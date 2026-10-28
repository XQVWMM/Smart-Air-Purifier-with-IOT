"""Seberapa jauh peringatan dini bisa ditingkatkan? Bandingkan model kecil (ESP32) vs model besar + fitur riwayat panjang."""
from datetime import timedelta
import numpy as np, pandas as pd
from sklearn.ensemble import RandomForestClassifier, HistGradientBoostingClassifier
from sklearn.metrics import average_precision_score, roc_auc_score
from sklearn.model_selection import TimeSeriesSplit

H, SEED = 5, 42
SEV = {"Udara Bersih": 0, "Polusi Ringan": 1, "Polusi Berat": 2}
df = pd.read_csv("dataset_air_purifier_10000.csv", parse_dates=["waktu"]).sort_values("waktu")
df = df.dropna(subset=["debu", "gas", "suhu", "kelembapan"]).reset_index(drop=True)
df["sev"] = df["status"].map(SEV)

def sel(kol, n):
    x = df[kol].diff(n); x[(df["waktu"] - df["waktu"].shift(n)) != timedelta(minutes=n)] = np.nan; return x

# --- fitur dasar (sama dengan model di ESP32)
for k in ("debu", "gas"):
    for n in (1, 3, 5): df[f"{k}_d{n}"] = sel(k, n)
    df[f"{k}_acc"] = df[f"{k}_d1"] - (df[f"{k}_d5"] - df[f"{k}_d1"]) / 4
df["suhu_d5"], df["lembap_d5"] = sel("suhu", 5), sel("kelembapan", 5)
df["debu_ke35"], df["gas_ke3"] = df["debu"] / 35, df["gas"] / 3
df["debu_proj"], df["gas_proj"] = (df["debu"] + 5 * df["debu_d1"]) / 35, (df["gas"] + 5 * df["gas_d1"]) / 3
BASE = ["debu", "gas", "suhu", "kelembapan", "sev", "debu_d1", "debu_d3", "debu_d5", "gas_d1", "gas_d3", "gas_d5",
        "debu_acc", "gas_acc", "suhu_d5", "lembap_d5", "debu_ke35", "gas_ke3", "debu_proj", "gas_proj"]

# --- fitur riwayat panjang (10 menit): maks/min/std jendela, selisih 10 menit, lonjakan terakhir
for k in ("debu", "gas"):
    df[f"{k}_d10"] = sel(k, 10)
    r = df[k].rolling(10)
    df[f"{k}_max10"], df[f"{k}_min10"], df[f"{k}_std10"] = r.max(), r.min(), r.std()
    df[f"{k}_rel1"] = df[f"{k}_d1"] / (df[k].shift(1) + 1)          # laju naik relatif
    df[f"{k}_naikberturut"] = (df[f"{k}_d1"] > 0).astype(int).rolling(3).sum()
PANJANG = BASE + [f"{k}_{s}" for k in ("debu", "gas") for s in ("d10", "max10", "min10", "std10", "rel1", "naikberturut")]

df["sev_nanti"] = df["sev"].shift(-H)
df.loc[(df["waktu"].shift(-H) - df["waktu"]) != timedelta(minutes=H), "sev_nanti"] = np.nan
d = df.dropna(subset=PANJANG + ["sev_nanti"]); d = d[d["sev"] < 2].reset_index(drop=True)
d["naik"] = (d["sev_nanti"] > d["sev"]).astype(int)
hari = len(d) / 1440
print(f"baris {len(d)}, kejadian memburuk {d['naik'].sum()} ({d['naik'].mean() * 100:.1f}%)")

def uji(nama, fitur, buat):
    oof = np.full(len(d), np.nan)
    for tr, te in TimeSeriesSplit(n_splits=5).split(d):
        tr = tr[tr < te[0] - H]
        oof[te] = buat().fit(d.loc[tr, fitur], d.loc[tr, "naik"]).predict_proba(d.loc[te, fitur])[:, 1]
    ok = ~np.isnan(oof); y, p = d.loc[ok, "naik"].to_numpy(), oof[ok]
    h = ok.sum() / 1440
    # recall pada ambang yang menghasilkan ~20 alarm palsu/hari
    best = 0.0; pre = 0.0
    for th in np.linspace(0.02, 0.98, 97):
        a = p >= th; fp = (a & (y == 0)).sum() / h
        if fp <= 20:
            rec = (a & (y == 1)).sum() / y.sum()
            if rec > best: best, pre = rec, (a & (y == 1)).sum() / max(a.sum(), 1)
    print(f"{nama:<42} AUC={roc_auc_score(y, p):.3f}  PR-AUC={average_precision_score(y, p):.3f}  "
          f"recall@20alarmpalsu/hari={best * 100:4.1f}% (presisi {pre * 100:4.1f}%)")

kecil = lambda: RandomForestClassifier(n_estimators=20, max_depth=8, min_samples_leaf=5, class_weight="balanced_subsample", random_state=SEED, n_jobs=-1)
besar = lambda: RandomForestClassifier(n_estimators=400, max_depth=14, min_samples_leaf=2, class_weight="balanced_subsample", random_state=SEED, n_jobs=-1)
hgb = lambda: HistGradientBoostingClassifier(max_iter=300, learning_rate=0.05, class_weight="balanced", random_state=SEED)
print("acak = PR-AUC", round(d["naik"].mean(), 3))
uji("RF kecil 20 pohon  | fitur ESP32 (saat ini)", BASE, kecil)
uji("RF kecil 20 pohon  | + riwayat 10 menit", PANJANG, kecil)
uji("RF besar 400 pohon | fitur ESP32", BASE, besar)
uji("RF besar 400 pohon | + riwayat 10 menit", PANJANG, besar)
uji("Gradient Boosting  | fitur ESP32", BASE, hgb)
uji("Gradient Boosting  | + riwayat 10 menit", PANJANG, hgb)
