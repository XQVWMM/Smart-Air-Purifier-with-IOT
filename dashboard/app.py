import spaces
import csv
import os
from collections import deque
from datetime import datetime, timedelta, timezone

import gradio as gr
import pandas as pd
from fastapi import HTTPException, Request
from fastapi.responses import FileResponse

API_KEY = os.environ.get("API_KEY", "")   # diisi lewat Settings > Secrets di Hugging Face
CSV_FILE = "data_sensor.csv"
# Urutan kolom CSV: 4 fitur sensor, lalu status & pwm (label hasil aturan ESP32)
KOLOM = ["waktu", "debu", "gas", "suhu", "kelembapan", "status", "pwm"]
WIB = timezone(timedelta(hours=7))

data = deque(maxlen=720)  # data terakhir yang ditampilkan (720 x 5 detik = 1 jam)

# Jika CSV lama (tanpa kolom suhu/kelembapan) masih ada, amankan dulu agar kolomnya tidak tercampur
if os.path.exists(CSV_FILE):
    with open(CSV_FILE, newline="") as f:
        _header = next(csv.reader(f), [])
    if _header != KOLOM:
        os.replace(CSV_FILE, "data_sensor_lama.csv")

if not os.path.exists(CSV_FILE):
    with open(CSV_FILE, "w", newline="") as f:
        csv.writer(f).writerow(KOLOM)

# ===================== SYARAT ZEROGPU =====================
# ZeroGPU mewajibkan minimal satu fungsi bertanda @spaces.GPU.
# Fungsi ini tidak pernah dipanggil, jadi kuota GPU tidak terpakai.
@spaces.GPU
def _syarat_zerogpu():
    return None

# ===================== DASHBOARD =====================
IKON = {"Udara Bersih": "🟢", "Polusi Ringan": "🟡", "Polusi Berat": "🔴"}

# Harus sama dengan batas di kode ESP32
BATAS_DEBU_RINGAN, BATAS_DEBU_BERAT = 35.0, 100.0     # µg/m³
BATAS_GAS_RINGAN, BATAS_GAS_BERAT = 3.0, 7.0          # ppm CO
BATAS_MAKSIMAL_DEBU, BATAS_MAKSIMAL_GAS = 1000.0, 2000.0
jumlah_ditolak = 0


def data_kosong():
    return pd.DataFrame({k: [] for k in KOLOM}).astype({"waktu": "datetime64[ns]"})


def angka_atau_none(nilai, minimum, maksimum):
    """Suhu/kelembapan opsional: kosong atau di luar rentang sensor DHT22 dianggap tidak terbaca."""
    try:
        v = float(nilai)
    except (TypeError, ValueError):
        return None
    return round(v, 1) if minimum <= v <= maksimum else None


def fmt(nilai, satuan, desimal=1):
    return "--" if nilai is None or pd.isna(nilai) else f"{nilai:.{desimal}f} {satuan}"


def update():
    if not data:
        kosong = data_kosong()
        return "### ⏳ Menunggu data dari ESP32...", kosong, kosong, kosong, kosong, kosong, kosong

    df = pd.DataFrame(list(data))
    tabel = df.tail(10).iloc[::-1]
    df["waktu"] = pd.to_datetime(df["waktu"])

    t = data[-1]
    persen = round(t["pwm"] / 255 * 100)
    ringkasan = (
        f"## {IKON.get(t['status'], '⚪')} {t['status']}\n\n"
        "| Debu | Gas CO | Suhu | Kelembapan | Kipas | Update terakhir |\n"
        "|---|---|---|---|---|---|\n"
        f"| **{t['debu']:.1f}** µg/m³ | **{t['gas']:.1f}** ppm "
        f"| **{fmt(t['suhu'], '°C')}** | **{fmt(t['kelembapan'], '%', 0)}** | **{persen}%** "
        f"| {t['waktu']} WIB |\n\n"
        f"<sub>Batas debu: ringan ≥ {BATAS_DEBU_RINGAN:g}, berat ≥ {BATAS_DEBU_BERAT:g} µg/m³ · "
        f"Batas CO: ringan ≥ {BATAS_GAS_RINGAN:g}, berat ≥ {BATAS_GAS_BERAT:g} ppm · "
        f"Data ditolak server: {jumlah_ditolak}</sub>"
    )
    return ringkasan, df, df, df, df, df, tabel


with gr.Blocks(title="Smart Air Purifier") as demo:
    gr.Markdown("# 🌬️ Smart Air Purifier — Dashboard IoT")
    ringkasan = gr.Markdown()
    with gr.Row():
        plot_debu = gr.LinePlot(x="waktu", y="debu", title="Kadar Debu (µg/m³)")
        plot_gas = gr.LinePlot(x="waktu", y="gas", title="Gas CO MQ-7 (ppm)")
    with gr.Row():
        plot_suhu = gr.LinePlot(x="waktu", y="suhu", title="Suhu Ruangan (°C)")
        plot_lembap = gr.LinePlot(x="waktu", y="kelembapan", title="Kelembapan (%)")
    plot_pwm = gr.LinePlot(x="waktu", y="pwm", title="PWM Kipas (0-255)")
    tabel = gr.Dataframe(label="10 data terakhir")
    gr.Markdown("📥 [Unduh semua data (CSV)](/api/csv)")

    keluaran = [ringkasan, plot_debu, plot_gas, plot_suhu, plot_lembap, plot_pwm, tabel]
    gr.Timer(3).tick(update, outputs=keluaran)   # refresh otomatis tiap 3 detik
    demo.load(update, outputs=keluaran)


# ===================== API: daftarkan ke internal FastAPI Gradio =====================
def _register_api(app_obj):
    @app_obj.post("/api/data")
    async def terima_data(request: Request):
        if API_KEY and request.headers.get("X-API-Key") != API_KEY:
            raise HTTPException(status_code=401, detail="API key salah")
        global jumlah_ditolak
        isi = await request.json()
        try:
            debu = float(isi.get("debu", 0))
            gas = float(isi.get("gas", 0))
        except (TypeError, ValueError):
            debu = gas = float("nan")
        # Validasi kedua di server (sama seperti dataValidUntukDikirim di ESP32)
        if not (0 <= debu <= BATAS_MAKSIMAL_DEBU and 0 <= gas <= BATAS_MAKSIMAL_GAS):
            jumlah_ditolak += 1
            raise HTTPException(status_code=422, detail="Nilai sensor di luar rentang wajar")
        baris = {
            "waktu": datetime.now(WIB).strftime("%Y-%m-%d %H:%M:%S"),
            "debu": round(debu, 1),
            "gas": round(gas, 1),
            "suhu": angka_atau_none(isi.get("suhu"), -40, 80),
            "kelembapan": angka_atau_none(isi.get("kelembapan"), 0, 100),
            "status": str(isi.get("status", "-")).strip(),
            "pwm": int(isi.get("pwm", 0)),
        }
        data.append(baris)
        with open(CSV_FILE, "a", newline="") as f:
            csv.DictWriter(f, fieldnames=KOLOM).writerow(baris)
        return {"ok": True}

    @app_obj.get("/api/csv")
    def unduh_csv():
        return FileResponse(CSV_FILE, media_type="text/csv", filename="data_sensor.csv")

    rute_kita = app_obj.router.routes[-2:]
    del app_obj.router.routes[-2:]
    app_obj.router.routes[0:0] = rute_kita

# ===================== LAUNCH =====================
# Gunakan demo.launch() agar Gradio handle port 7860 sendiri —
# menghindari konflik bind yang terjadi saat gr.mount_gradio_app + uvicorn.run()
# dipanggil bersamaan di Gradio versi baru.
_result = demo.launch(
    server_name="0.0.0.0",
    server_port=7860,
    prevent_thread_lock=True,
    quiet=True,
    ssr_mode=False,
)

# Coba akses internal FastAPI Gradio untuk mendaftarkan /api/data & /api/csv
# Gradio 3.x / 4.x  : launch() mengembalikan (app, local_url, share_url)
# Gradio 5.x / 6.x  : bisa via demo.server.app atau demo.app
_app = None

if isinstance(_result, tuple) and _result:
    _candidate = _result[0]
    if hasattr(_candidate, "add_api_route"):   # FastAPI instance
        _app = _candidate

if _app is None and hasattr(demo, "server") and demo.server is not None:
    if hasattr(demo.server, "app"):
        _app = demo.server.app

if _app is None and hasattr(demo, "app"):
    _app = demo.app

if _app is not None:
    _register_api(_app)
    print("✓ API routes /api/data dan /api/csv berhasil didaftarkan.")
else:
    print("⚠ Tidak bisa mendaftarkan API routes — cek versi Gradio.")

# Blokir thread agar proses tetap hidup
demo.block_thread()
