"""Eksperimen: apakah model prediksi 5 menit ke depan lebih baik dari 'status sekarang = status nanti'?"""
from datetime import timedelta
import numpy as np, pandas as pd
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import f1_score, confusion_matrix

SEV = {"Udara Bersih": 0, "Polusi Ringan": 1, "Polusi Berat": 2}
H = 5

df = pd.read_csv("dataset_air_purifier_10000.csv", parse_dates=["waktu"]).sort_values("waktu").reset_index(drop=True)
df = df.dropna(subset=["debu", "gas", "suhu", "kelembapan"]).reset_index(drop=True)
df["sev"] = df["status"].map(SEV)

# fitur tren dihitung hanya jika selisih waktunya memang 1/5 menit (celah data tidak ikut)
for kol in ("debu", "gas"):
    for n in (1, 3, 5):
        d = df[kol].diff(n)
        d[(df["waktu"] - df["waktu"].shift(n)) != timedelta(minutes=n)] = np.nan
        df[f"{kol}_d{n}"] = d
jam = df["waktu"].dt.hour + df["waktu"].dt.minute / 60
df["jam_sin"], df["jam_cos"] = np.sin(2 * np.pi * jam / 24), np.cos(2 * np.pi * jam / 24)
df["sev_nanti"] = df["sev"].shift(-H)
df.loc[(df["waktu"].shift(-H) - df["waktu"]) != timedelta(minutes=H), "sev_nanti"] = np.nan

BASE = ["debu", "gas", "suhu", "kelembapan"]
TREN = [f"{k}_d{n}" for k in ("debu", "gas") for n in (1, 3, 5)]
VAR = {"A sensor saja": BASE, "B sensor+tren": BASE + TREN, "C sensor+tren+jam": BASE + TREN + ["jam_sin", "jam_cos"]}

d = df.dropna(subset=BASE + TREN + ["sev_nanti"]).reset_index(drop=True)
d["sev_nanti"] = d["sev_nanti"].astype(int)
n_uji = int(len(d) * 0.2)
tr, te = d.iloc[:-n_uji - H], d.iloc[-n_uji:]
y_tr, y_te = tr["sev_nanti"], te["sev_nanti"]

def laporan(nama, pred):
    f1 = f1_score(y_te, pred, average="macro", zero_division=0)
    naik = (y_te > te["sev"]).to_numpy()                # kejadian: udara akan MEMBURUK dalam 5 menit
    tertangkap = ((pred > te["sev"].to_numpy()) & naik).sum()
    alarm = (pred > te["sev"].to_numpy())
    palsu = (alarm & ~naik).sum()
    print(f"{nama:<22} macro-F1={f1:.3f} | memburuk: {naik.sum()} kejadian, terdeteksi dini {tertangkap} "
          f"({tertangkap / max(naik.sum(), 1) * 100:.0f}%) | alarm palsu {palsu} ({palsu / max(alarm.sum(), 1) * 100:.0f}% dari alarm)")

print(f"Latih {len(tr)} | Uji {len(te)} | uji: {y_te.value_counts().sort_index().to_dict()} | memburuk di uji: {(y_te > te['sev']).sum()}")
laporan("Baseline (sama dgn skrg)", te["sev"].to_numpy())
for nama, fit in VAR.items():
    rf = RandomForestClassifier(n_estimators=100, max_depth=10, min_samples_leaf=3, class_weight="balanced",
                                random_state=42, n_jobs=-1).fit(tr[fit], y_tr)
    laporan(nama, rf.predict(te[fit]))
