"""
Model PERINGATAN DINI untuk Smart Air Purifier
===============================================
Tugas  : memprediksi peluang udara MEMBURUK dalam H menit ke depan
         (Bersih -> Ringan/Berat, atau Ringan -> Berat), dari tren 6 menit terakhir.
Dipakai: ESP32 hanya MENAIKKAN kecepatan kipas jika peluang >= ambang. Aturan ambang batas
         tetap menjadi lantai pengaman (model tidak pernah menurunkan kipas).
Output : hasil_peringatan/model_rf_peringatan.h   (model, otomatis)
         hasil_peringatan/metrik_peringatan.json
         hasil_peringatan/uji_paritas.csv         (contoh data untuk mencocokkan ESP32 vs Python)

Jalankan: python train_peringatan_dini.py [path_csv]
"""
import json
import sys
from datetime import timedelta
from pathlib import Path

import numpy as np
import pandas as pd
from sklearn.ensemble import RandomForestClassifier
from sklearn.model_selection import TimeSeriesSplit

CSV_PATH = sys.argv[1] if len(sys.argv) > 1 else "dataset_air_purifier_10000.csv"
OUT = Path("hasil_peringatan"); OUT.mkdir(exist_ok=True)
H = 5                       # menit ke depan
MAKS_ALARM_PALSU_PER_HARI = 30
SEED = 42
SEV = {"Udara Bersih": 0, "Polusi Ringan": 1, "Polusi Berat": 2}

# Urutan fitur: HARUS sama persis dengan ai_peringatan.h di ESP32
FIT = ["debu", "gas", "suhu", "kelembapan", "sev",
       "debu_d1", "debu_d3", "debu_d5", "gas_d1", "gas_d3", "gas_d5", "debu_acc", "gas_acc",
       "suhu_d5", "lembap_d5", "debu_ke35", "gas_ke3", "debu_proj", "gas_proj"]

# ------------------------------------------------------------------ data
df = pd.read_csv(CSV_PATH)
if "waktu" not in df.columns:
    df = pd.read_csv(CSV_PATH, sep=";", decimal=",")
df["waktu"] = pd.to_datetime(df["waktu"])
df = df.sort_values("waktu").dropna(subset=["debu", "gas", "suhu", "kelembapan"]).reset_index(drop=True)

# Data asli dari alat dikirim tiap ~1 detik, sedangkan model dilatih & dijalankan di ESP32 per MENIT
# (rata-rata 1 menit). Jika data lebih rapat dari itu, rata-ratakan dulu per menit.
if df["waktu"].diff().median() < timedelta(seconds=45):
    print("Data rapat (<45 detik): dirata-ratakan per menit, status dihitung ulang dari rata-rata.")
    df = (df.set_index("waktu")[["debu", "gas", "suhu", "kelembapan"]].resample("1min").mean()
            .dropna().reset_index())
    sev_baru = np.where((df["debu"] >= 100) | (df["gas"] >= 7), 2,
                        np.where((df["debu"] >= 35) | (df["gas"] >= 3), 1, 0))
    df["status"] = pd.Series(sev_baru).map({v: k for k, v in SEV.items()})
df["sev"] = df["status"].map(SEV)


def selisih(kol, n):
    """Selisih n menit ke belakang; kosong jika ada celah data (alat sempat mati)."""
    d = df[kol].diff(n)
    d[(df["waktu"] - df["waktu"].shift(n)) != timedelta(minutes=n)] = np.nan
    return d


for k in ("debu", "gas"):
    df[f"{k}_d1"], df[f"{k}_d3"], df[f"{k}_d5"] = selisih(k, 1), selisih(k, 3), selisih(k, 5)
    df[f"{k}_acc"] = df[f"{k}_d1"] - (df[f"{k}_d5"] - df[f"{k}_d1"]) / 4
df["suhu_d5"], df["lembap_d5"] = selisih("suhu", 5), selisih("kelembapan", 5)
df["debu_ke35"], df["gas_ke3"] = df["debu"] / 35, df["gas"] / 3
df["debu_proj"] = (df["debu"] + 5 * df["debu_d1"]) / 35
df["gas_proj"] = (df["gas"] + 5 * df["gas_d1"]) / 3

df["sev_nanti"] = df["sev"].shift(-H)
df.loc[(df["waktu"].shift(-H) - df["waktu"]) != timedelta(minutes=H), "sev_nanti"] = np.nan
d = df.dropna(subset=FIT + ["sev_nanti"])
d = d[d["sev"] < 2].reset_index(drop=True)          # yang sudah Berat tidak bisa memburuk lagi
d["naik"] = (d["sev_nanti"] > d["sev"]).astype(int)
print(f"Baris: {len(d)} | kejadian memburuk dalam {H} menit: {d['naik'].sum()} ({d['naik'].mean() * 100:.1f}%)")


def buat_model():
    # kecil agar muat di ESP32
    return RandomForestClassifier(n_estimators=20, max_depth=8, min_samples_leaf=5,
                                  class_weight="balanced_subsample", random_state=SEED, n_jobs=-1)


# ------------------------------------------------------------------ validasi lintas waktu
oof = np.full(len(d), np.nan)
for tr, te in TimeSeriesSplit(n_splits=5).split(d):
    tr = tr[tr < te[0] - H]
    oof[te] = buat_model().fit(d.loc[tr, FIT], d.loc[tr, "naik"]).predict_proba(d.loc[te, FIT])[:, 1]
ok = ~np.isnan(oof)
y, p = d.loc[ok, "naik"].to_numpy(), oof[ok]
hari = ok.sum() / 1440

print("\nambang  recall  presisi  alarm_palsu/hari")
tabel, pilih = [], None
for th in np.arange(0.2, 0.81, 0.05):
    a = p >= th
    tp, fp = int((a & (y == 1)).sum()), int((a & (y == 0)).sum())
    rec, pre, fph = tp / y.sum(), tp / max(a.sum(), 1), fp / hari
    tabel.append({"ambang": round(float(th), 2), "recall": round(rec, 3), "presisi": round(pre, 3), "alarm_palsu_per_hari": round(fph, 1)})
    print(f"{th:5.2f}  {rec * 100:5.1f}%  {pre * 100:6.1f}%  {fph:10.1f}")
    if fph <= MAKS_ALARM_PALSU_PER_HARI and pilih is None:
        pilih = tabel[-1]            # ambang terendah (recall tertinggi) yang alarm palsunya masih wajar
if pilih is None:
    pilih = tabel[-1]
AMBANG = pilih["ambang"]
print(f"\nAmbang dipilih: {AMBANG} -> {pilih}")

# ------------------------------------------------------------------ model final (semua data)
final = buat_model().fit(d[FIT], d["naik"])
print(f"Model final: {len(final.estimators_)} pohon, {sum(e.tree_.node_count for e in final.estimators_)} node")
print("Pentingnya fitur (gini):")
print(pd.Series(final.feature_importances_, index=FIT).sort_values(ascending=False).round(3).head(8).to_string())


# ------------------------------------------------------------------ ekspor C++
def pohon_ke_cpp(est, nama):
    t = est.tree_
    baris = [f"static inline void {nama}(const float* x, float* votes) {{"]

    def rec(node, indent):
        pad = "  " * indent
        if t.children_left[node] == -1:
            nilai = t.value[node][0]
            nilai = nilai / nilai.sum()
            for i, v in enumerate(nilai):
                if v > 0:
                    baris.append(f"{pad}votes[{i}] += {v:.4f}f;")
            return
        baris.append(f"{pad}if (x[{t.feature[node]}] <= {t.threshold[node]:.4f}f) {{")
        rec(t.children_left[node], indent + 1)
        baris.append(f"{pad}}} else {{")
        rec(t.children_right[node], indent + 1)
        baris.append(f"{pad}}}")

    rec(0, 1)
    baris.append("}")
    return "\n".join(baris)


n_pohon = len(final.estimators_)
h = ["// Dibuat otomatis oleh train_peringatan_dini.py - JANGAN diedit manual.",
     f"// Peluang udara MEMBURUK dalam {H} menit. Urutan fitur x[]:",
     "//   " + ", ".join(f"{i}={f}" for i, f in enumerate(FIT)),
     "#pragma once", "",
     f"#define AI_HORIZON_MENIT {H}",
     f"#define AI_AMBANG_DEFAULT {AMBANG}f",
     f"#define AI_JUMLAH_FITUR {len(FIT)}",
     f"#define AI_JUMLAH_POHON {n_pohon}", ""]
for i, e in enumerate(final.estimators_):
    h += [pohon_ke_cpp(e, f"aiPohon{i}"), ""]
h += ["// Mengembalikan peluang (0..1) bahwa udara akan memburuk.",
      "inline float aiPeluangMemburuk(const float* x) {",
      "  float votes[2] = {0, 0};"]
h += [f"  aiPohon{i}(x, votes);" for i in range(n_pohon)]
h += [f"  return votes[1] / {n_pohon}.0f;", "}"]
(OUT / "model_rf_peringatan.h").write_text("\n".join(h), encoding="utf-8")

# ------------------------------------------------------------------ data uji paritas (jendela 6 menit -> peluang sklearn)
rng = np.random.default_rng(SEED)
raw = df.set_index("waktu")
contoh = []
for idx in rng.choice(np.arange(5, len(d)), size=300, replace=False):
    w = d.loc[idx, "waktu"]
    jendela = raw.loc[w - timedelta(minutes=5): w]
    if len(jendela) != 6:
        continue
    peluang = float(final.predict_proba(d.loc[[idx], FIT])[0, 1])
    baris = {"waktu": str(w), "peluang_python": peluang}
    for i, (_, r) in enumerate(jendela.iterrows()):
        baris.update({f"debu{i}": r["debu"], f"gas{i}": r["gas"], f"suhu{i}": r["suhu"],
                      f"lembap{i}": r["kelembapan"], f"sev{i}": int(r["sev"])})
    contoh.append(baris)
pd.DataFrame(contoh).to_csv(OUT / "uji_paritas.csv", index=False)

(OUT / "metrik_peringatan.json").write_text(json.dumps(
    {"horizon_menit": H, "ambang_dipilih": pilih, "tabel_ambang": tabel, "fitur": FIT,
     "jumlah_baris": len(d), "persen_kejadian_memburuk": round(float(d["naik"].mean() * 100), 2)},
    indent=2), encoding="utf-8")
print(f"\nTersimpan di {OUT.resolve()}  (contoh paritas: {len(contoh)})")
