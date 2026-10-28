"""Eksperimen 2: model 'peringatan dini' = P(udara memburuk dalam H menit), diuji lintas lipatan waktu."""
import sys
from datetime import timedelta
import numpy as np, pandas as pd
from sklearn.ensemble import RandomForestClassifier
from sklearn.model_selection import TimeSeriesSplit

H = int(sys.argv[1]) if len(sys.argv) > 1 else 5
SEV = {"Udara Bersih": 0, "Polusi Ringan": 1, "Polusi Berat": 2}

df = pd.read_csv("dataset_air_purifier_10000.csv", parse_dates=["waktu"]).sort_values("waktu").reset_index(drop=True)
df = df.dropna(subset=["debu", "gas", "suhu", "kelembapan"]).reset_index(drop=True)
df["sev"] = df["status"].map(SEV)

def selisih(kol, n):
    d = df[kol].diff(n)
    d[(df["waktu"] - df["waktu"].shift(n)) != timedelta(minutes=n)] = np.nan
    return d

for k in ("debu", "gas"):
    df[f"{k}_d1"], df[f"{k}_d3"], df[f"{k}_d5"] = selisih(k, 1), selisih(k, 3), selisih(k, 5)
    df[f"{k}_acc"] = df[f"{k}_d1"] - (df[f"{k}_d5"] - df[f"{k}_d1"]) / 4      # percepatan
df["suhu_d5"], df["lembap_d5"] = selisih("suhu", 5), selisih("kelembapan", 5)
# jarak ke ambang & proyeksi linear 5 menit ke depan
df["debu_ke35"], df["gas_ke3"] = df["debu"] / 35, df["gas"] / 3
df["debu_proj"] = (df["debu"] + 5 * df["debu_d1"]) / 35
df["gas_proj"] = (df["gas"] + 5 * df["gas_d1"]) / 3

FIT = ["debu", "gas", "suhu", "kelembapan", "sev",
       "debu_d1", "debu_d3", "debu_d5", "gas_d1", "gas_d3", "gas_d5", "debu_acc", "gas_acc",
       "suhu_d5", "lembap_d5", "debu_ke35", "gas_ke3", "debu_proj", "gas_proj"]

df["sev_nanti"] = df["sev"].shift(-H)
df.loc[(df["waktu"].shift(-H) - df["waktu"]) != timedelta(minutes=H), "sev_nanti"] = np.nan
d = df.dropna(subset=FIT + ["sev_nanti"]).reset_index(drop=True)
d = d[d["sev"] < 2].reset_index(drop=True)                 # kalau sudah Berat tidak bisa memburuk lagi
d["naik"] = (d["sev_nanti"] > d["sev"]).astype(int)

oof = np.full(len(d), np.nan)
for tr, te in TimeSeriesSplit(n_splits=5).split(d):
    tr = tr[tr < te[0] - H]                                 # beri jarak
    m = RandomForestClassifier(n_estimators=200, max_depth=10, min_samples_leaf=3, class_weight="balanced_subsample",
                               random_state=42, n_jobs=-1).fit(d.loc[tr, FIT], d.loc[tr, "naik"])
    oof[te] = m.predict_proba(d.loc[te, FIT])[:, 1]

ok = ~np.isnan(oof)
y, p = d.loc[ok, "naik"].to_numpy(), oof[ok]
print(f"H={H} menit | baris dievaluasi {ok.sum()} | kejadian memburuk {y.sum()} ({y.mean() * 100:.1f}%)")
print("ambang  recall  presisi  alarm_palsu/hari(24 jam)")
hari = ok.sum() / 1440
for th in (0.2, 0.3, 0.4, 0.5, 0.6, 0.7):
    a = p >= th
    tp, fp = (a & (y == 1)).sum(), (a & (y == 0)).sum()
    print(f"{th:>5}  {tp / y.sum() * 100:5.1f}%  {tp / max(a.sum(), 1) * 100:6.1f}%  {fp / hari:8.1f}")
