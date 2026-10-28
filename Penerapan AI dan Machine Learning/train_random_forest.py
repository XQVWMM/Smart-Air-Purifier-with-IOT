"""
Training Random Forest untuk Smart Air Purifier
================================================
Input : dataset_air_purifier_10000.csv  (waktu, debu, gas, suhu, kelembapan, status, pwm)
Output: folder hasil_training/ berisi model, grafik, metrik, dan header C++ untuk ESP32.

Dua mode (ubah HORIZON_MENIT di bagian KONFIGURASI):
  HORIZON_MENIT = 0  -> klasifikasi status udara SAAT INI dari 4 sensor
  HORIZON_MENIT > 0  -> prediksi status udara N MENIT KE DEPAN (memakai tren + jam)

Instalasi:
  pip install pandas numpy scikit-learn matplotlib joblib
Jalankan:
  python train_random_forest.py
"""

import json
from datetime import timedelta
from pathlib import Path

import joblib
import matplotlib
matplotlib.use("Agg")          # simpan grafik ke file, tanpa membuka jendela
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from sklearn.dummy import DummyClassifier
from sklearn.ensemble import RandomForestClassifier
from sklearn.inspection import permutation_importance
from sklearn.metrics import (ConfusionMatrixDisplay, accuracy_score,
                             balanced_accuracy_score, classification_report,
                             confusion_matrix, f1_score)
from sklearn.model_selection import GridSearchCV, TimeSeriesSplit

# =============================================================================
# 1. KONFIGURASI
# =============================================================================
CSV_PATH = "dataset_air_purifier_10000.csv"   # pakai versi koma/titik, BUKAN versi _excel
OUT_DIR = Path("hasil_training")
HORIZON_MENIT = 0          # 0 = status saat ini; mis. 5 = prediksi 5 menit ke depan
SAMPLE_DETIK = 60          # jarak antar baris pada dataset
TEST_RATIO = 0.2           # 20% data paling akhir dipakai sebagai data uji
SEED = 42

FITUR_SENSOR = ["debu", "gas", "suhu", "kelembapan"]
URUTAN_LABEL = ["Udara Bersih", "Polusi Ringan", "Polusi Berat"]

# Rentang wajar sensor (sama dengan validasi di server). Di luar rentang = dibuang.
RENTANG = {"debu": (0, 1000), "gas": (0, 2000), "suhu": (-40, 80), "kelembapan": (0, 100)}

OUT_DIR.mkdir(exist_ok=True)


def judul(teks):
    print("\n" + "=" * 70 + f"\n{teks}\n" + "=" * 70)


# =============================================================================
# 2. MEMUAT & MEMBERSIHKAN DATA
# =============================================================================
judul("1. MEMUAT DATA")
df = pd.read_csv(CSV_PATH)
if "waktu" not in df.columns:   # file versi Excel: pemisah ';' dan desimal ','
    print("Header tidak terbaca dengan koma, mencoba format Excel (sep=';', decimal=',')")
    df = pd.read_csv(CSV_PATH, sep=";", decimal=",")
if "waktu" not in df.columns:
    raise SystemExit(f"Kolom 'waktu' tidak ditemukan. Kolom yang terbaca: {list(df.columns)}")
df["waktu"] = pd.to_datetime(df["waktu"])
df = df.sort_values("waktu").reset_index(drop=True)
print(f"Baris awal      : {len(df)}")
print(f"Periode         : {df['waktu'].min()}  ->  {df['waktu'].max()}")
print("Nilai kosong per kolom:")
print(df.isna().sum().to_string())

# Buang baris dengan sensor kosong (mis. DHT22 gagal baca) atau di luar rentang wajar
df = df.dropna(subset=FITUR_SENSOR)
for kol, (lo, hi) in RENTANG.items():
    df = df[df[kol].between(lo, hi)]
df = df.reset_index(drop=True)
print(f"Baris setelah dibersihkan: {len(df)}")

print("\nStatistik sensor:")
print(df[FITUR_SENSOR].describe().round(2).to_string())
print("\nDistribusi status:")
print((df["status"].value_counts(normalize=True) * 100).round(1).to_string())

# =============================================================================
# 3. FITUR & TARGET
# =============================================================================
judul("2. MEMBENTUK FITUR DAN TARGET")
FITUR = list(FITUR_SENSOR)

if HORIZON_MENIT == 0:
    df["target"] = df["status"]
    print("Mode: klasifikasi status SAAT INI dari debu, gas, suhu, kelembapan.")
else:
    step = (HORIZON_MENIT * 60) // SAMPLE_DETIK
    # Fitur tren: perubahan debu & gas dalam 1 dan 5 langkah terakhir
    for kol in ("debu", "gas"):
        df[f"{kol}_d1"] = df[kol].diff(1)
        df[f"{kol}_d5"] = df[kol].diff(5)
    # Waktu dalam sehari (sin/cos agar 23:59 dekat dengan 00:00)
    jam = df["waktu"].dt.hour + df["waktu"].dt.minute / 60
    df["jam_sin"] = np.sin(2 * np.pi * jam / 24)
    df["jam_cos"] = np.cos(2 * np.pi * jam / 24)
    FITUR += ["debu_d1", "debu_d5", "gas_d1", "gas_d5", "jam_sin", "jam_cos"]

    # Target = status N menit ke depan. Baris yang selisih waktunya tidak pas
    # (karena alat sempat mati) dibuang agar label tidak salah.
    df["target"] = df["status"].shift(-step)
    selisih = df["waktu"].shift(-step) - df["waktu"]
    df.loc[selisih != timedelta(minutes=HORIZON_MENIT), "target"] = np.nan
    print(f"Mode: prediksi status {HORIZON_MENIT} menit ke depan ({step} langkah).")

df = df.dropna(subset=FITUR + ["target"]).reset_index(drop=True)
print(f"Fitur   : {FITUR}")
print(f"Baris siap training: {len(df)}")

# =============================================================================
# 4. PEMBAGIAN DATA (BERURUTAN WAKTU, BUKAN ACAK)
# =============================================================================
judul("3. PEMBAGIAN DATA LATIH / UJI")
# Data sensor adalah deret waktu: mengacak baris membuat baris bertetangga
# (yang hampir kembar) masuk ke latih dan uji sekaligus -> skor terlihat terlalu bagus.
n_uji = int(len(df) * TEST_RATIO)
train, test = df.iloc[:-n_uji], df.iloc[-n_uji:]
if HORIZON_MENIT > 0:   # beri jarak agar label latih tidak "mengintip" periode uji
    train = train.iloc[: -((HORIZON_MENIT * 60) // SAMPLE_DETIK)]

X_train, y_train = train[FITUR], train["target"]
X_test, y_test = test[FITUR], test["target"]
print(f"Latih: {len(train)} baris ({train['waktu'].min()} -> {train['waktu'].max()})")
print(f"Uji  : {len(test)} baris ({test['waktu'].min()} -> {test['waktu'].max()})")
print("Distribusi latih:", y_train.value_counts().to_dict())
print("Distribusi uji  :", y_test.value_counts().to_dict())
if set(y_test.unique()) - set(y_train.unique()):
    print("PERINGATAN: ada kelas di data uji yang tidak ada di data latih.")

# =============================================================================
# 5. BASELINE
# =============================================================================
judul("4. BASELINE (selalu menebak kelas terbanyak)")
base = DummyClassifier(strategy="most_frequent").fit(X_train, y_train)
pred_base = base.predict(X_test)
print(f"Akurasi baseline : {accuracy_score(y_test, pred_base):.4f}")
print(f"Macro-F1 baseline: {f1_score(y_test, pred_base, average='macro', zero_division=0):.4f}")
print("Model harus jauh lebih baik dari angka ini.")

# =============================================================================
# 6. TUNING HYPERPARAMETER
# =============================================================================
judul("5. TUNING RANDOM FOREST (GridSearchCV + TimeSeriesSplit)")
param_grid = {
    "n_estimators": [100, 300],
    "max_depth": [None, 12],
    "min_samples_leaf": [1, 3, 5],
    "max_features": ["sqrt", None],
}
rf = RandomForestClassifier(class_weight="balanced", random_state=SEED, n_jobs=-1)
cv = TimeSeriesSplit(n_splits=3)
grid = GridSearchCV(rf, param_grid, cv=cv, scoring="f1_macro", n_jobs=-1, verbose=1)
grid.fit(X_train, y_train)

print(f"Parameter terbaik : {grid.best_params_}")
print(f"Macro-F1 validasi : {grid.best_score_:.4f}")
model = grid.best_estimator_

# =============================================================================
# 7. EVALUASI PADA DATA UJI
# =============================================================================
judul("6. EVALUASI PADA DATA UJI")
pred = model.predict(X_test)
label_ada = [l for l in URUTAN_LABEL if l in set(model.classes_)]

acc = accuracy_score(y_test, pred)
bacc = balanced_accuracy_score(y_test, pred)
f1m = f1_score(y_test, pred, average="macro", zero_division=0)
print(f"Akurasi          : {acc:.4f}")
print(f"Balanced akurasi : {bacc:.4f}")
print(f"Macro-F1         : {f1m:.4f}")
print("\nLaporan per kelas:")
print(classification_report(y_test, pred, labels=label_ada, digits=4, zero_division=0))

cm = confusion_matrix(y_test, pred, labels=label_ada)
fig, ax = plt.subplots(figsize=(6, 5))
ConfusionMatrixDisplay(cm, display_labels=label_ada).plot(ax=ax, cmap="Blues", colorbar=False)
ax.set_title("Confusion Matrix (data uji)")
plt.xticks(rotation=20)
plt.tight_layout()
fig.savefig(OUT_DIR / "confusion_matrix.png", dpi=150)
plt.close(fig)

pd.DataFrame({"waktu": test["waktu"], "asli": y_test, "prediksi": pred}) \
    .to_csv(OUT_DIR / "prediksi_data_uji.csv", index=False)

# =============================================================================
# 8. FITUR PALING BERPENGARUH
# =============================================================================
judul("7. PENTINGNYA FITUR")
imp_gini = pd.Series(model.feature_importances_, index=FITUR)
perm = permutation_importance(model, X_test, y_test, scoring="f1_macro",
                              n_repeats=10, random_state=SEED, n_jobs=-1)
imp_perm = pd.Series(perm.importances_mean, index=FITUR)
tabel_imp = pd.DataFrame({"gini": imp_gini, "permutasi": imp_perm}).sort_values("permutasi", ascending=False)
print(tabel_imp.round(4).to_string())
print("Permutasi = turunnya macro-F1 jika fitur itu diacak. Lebih jujur daripada gini.")

fig, ax = plt.subplots(figsize=(7, 4))
tabel_imp["permutasi"][::-1].plot.barh(ax=ax, color="#2a7ae2")
ax.set_xlabel("Penurunan macro-F1 saat fitur diacak")
ax.set_title("Pentingnya fitur (permutation importance)")
plt.tight_layout()
fig.savefig(OUT_DIR / "feature_importance.png", dpi=150)
plt.close(fig)

# =============================================================================
# 9. UJI KETAHANAN (ROBUSTNESS) TERHADAP NOISE SENSOR
# =============================================================================
judul("8. UJI KETAHANAN TERHADAP NOISE")
rng = np.random.default_rng(SEED)
hasil_noise = {}
for sigma in (0.0, 0.05, 0.10, 0.20):
    X_noisy = X_test * (1 + rng.normal(0, sigma, X_test.shape))
    f1n = f1_score(y_test, model.predict(X_noisy), average="macro", zero_division=0)
    hasil_noise[f"{int(sigma * 100)}%"] = round(f1n, 4)
    print(f"Noise {int(sigma * 100):>2}% -> macro-F1 = {f1n:.4f}")

# =============================================================================
# 10. SIMPAN MODEL & METADATA
# =============================================================================
judul("9. MENYIMPAN MODEL")
joblib.dump({"model": model, "fitur": FITUR, "kelas": list(model.classes_),
             "horizon_menit": HORIZON_MENIT}, OUT_DIR / "model_rf.joblib")
metrik = {
    "horizon_menit": HORIZON_MENIT, "fitur": FITUR, "parameter_terbaik": grid.best_params_,
    "f1_validasi": round(grid.best_score_, 4), "akurasi_uji": round(acc, 4),
    "balanced_akurasi_uji": round(bacc, 4), "macro_f1_uji": round(f1m, 4),
    "macro_f1_baseline": round(f1_score(y_test, pred_base, average="macro", zero_division=0), 4),
    "macro_f1_dengan_noise": hasil_noise,
    "jumlah_latih": len(train), "jumlah_uji": len(test),
}
(OUT_DIR / "metrik.json").write_text(json.dumps(metrik, indent=2, ensure_ascii=False), encoding="utf-8")
print(f"Tersimpan di {OUT_DIR.resolve()}")
print("Muat ulang model nanti dengan:  d = joblib.load('hasil_training/model_rf.joblib'); d['model'].predict(...)")

# =============================================================================
# 11. MODEL KECIL UNTUK ESP32 + EKSPOR KE C++
# =============================================================================
judul("10. MODEL KECIL UNTUK ESP32")
# Model hasil tuning (100-300 pohon) terlalu besar untuk mikrokontroler.
# Latih versi ringkas: sedikit pohon, kedalaman dibatasi.
kecil = RandomForestClassifier(n_estimators=15, max_depth=8, min_samples_leaf=5,
                               class_weight="balanced", random_state=SEED, n_jobs=-1)
kecil.fit(X_train, y_train)
pred_kecil = kecil.predict(X_test)
print(f"Model kecil: akurasi={accuracy_score(y_test, pred_kecil):.4f}  "
      f"macro-F1={f1_score(y_test, pred_kecil, average='macro', zero_division=0):.4f}")
total_node = sum(e.tree_.node_count for e in kecil.estimators_)
print(f"Total node pohon: {total_node} (makin sedikit makin ringan di flash ESP32)")


def pohon_ke_cpp(est, nama):
    """Ubah satu pohon keputusan menjadi fungsi C++ if/else yang menambah 'suara' ke votes[]."""
    t = est.tree_
    baris = [f"static inline void {nama}(const float* x, float* votes) {{"]

    def rec(node, indent):
        pad = "  " * indent
        if t.children_left[node] == -1:                      # daun
            nilai = t.value[node][0]
            nilai = nilai / nilai.sum()
            for i, p in enumerate(nilai):
                if p > 0:
                    baris.append(f"{pad}votes[{i}] += {p:.4f}f;")
            return
        baris.append(f"{pad}if (x[{t.feature[node]}] <= {t.threshold[node]:.4f}f) {{")
        rec(t.children_left[node], indent + 1)
        baris.append(f"{pad}}} else {{")
        rec(t.children_right[node], indent + 1)
        baris.append(f"{pad}}}")

    rec(0, 1)
    baris.append("}")
    return "\n".join(baris)


def votes_manual(model_rf, x):
    """Meniru persis logika C++ di Python, untuk memastikan hasil ekspor sama dengan sklearn."""
    votes = np.zeros(len(model_rf.classes_))
    for est in model_rf.estimators_:
        t, node = est.tree_, 0
        while t.children_left[node] != -1:
            node = t.children_left[node] if np.float32(x[t.feature[node]]) <= np.float32(t.threshold[node]) \
                else t.children_right[node]
        v = t.value[node][0]
        votes += v / v.sum()
    return votes


header = [
    "// Dibuat otomatis oleh train_random_forest.py - JANGAN diedit manual.",
    f"// Mode: {'status saat ini' if HORIZON_MENIT == 0 else f'prediksi {HORIZON_MENIT} menit ke depan'}",
    "// Urutan fitur untuk array x[] HARUS persis:",
    "//   " + ", ".join(f"x[{i}]={f}" for i, f in enumerate(FITUR)),
    "#pragma once",
    "",
    f"const int JUMLAH_KELAS = {len(kecil.classes_)};",
    "const char* NAMA_KELAS[] = {" + ", ".join(f'"{k}"' for k in kecil.classes_) + "};",
    "",
]
for i, est in enumerate(kecil.estimators_):
    header.append(pohon_ke_cpp(est, f"pohon{i}"))
    header.append("")
header.append("// Mengembalikan indeks kelas (lihat NAMA_KELAS). Suara terbanyak menang.")
header.append("inline int prediksiStatus(const float* x) {")
header.append("  float votes[JUMLAH_KELAS] = {0};")
for i in range(len(kecil.estimators_)):
    header.append(f"  pohon{i}(x, votes);")
header.append("  int terbaik = 0;")
header.append("  for (int k = 1; k < JUMLAH_KELAS; k++) if (votes[k] > votes[terbaik]) terbaik = k;")
header.append("  return terbaik;")
header.append("}")
(OUT_DIR / "model_rf_esp32.h").write_text("\n".join(header), encoding="utf-8")

# Verifikasi: logika ekspor harus sama dengan prediksi sklearn
contoh = X_test.to_numpy()[:500]
cocok = np.mean([kecil.classes_[np.argmax(votes_manual(kecil, x))] == p
                 for x, p in zip(contoh, kecil.predict(X_test.iloc[:500]))])
print(f"Kecocokan ekspor C++ vs sklearn pada 500 contoh: {cocok * 100:.1f}%")
print(f"Header ESP32 tersimpan: {OUT_DIR / 'model_rf_esp32.h'}")
print("\nSELESAI.")
