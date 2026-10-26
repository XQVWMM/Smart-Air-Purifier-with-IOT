// Generator dataset SINTETIS Smart Air Purifier (simulasi ruangan, bukan hasil pengukuran alat asli).
// Label status & pwm dihitung dengan aturan yang sama persis dengan air-purifier-kel5.ino.
// Jalankan: node generate_dataset.js
const fs = require("fs");

const N = 10000;            // jumlah baris
const STEP = 60;            // detik antar sampel
const START = Date.UTC(2026, 9, 19, 0, 0, 0) - 7 * 3600 * 1000;   // 2026-10-19 00:00 WIB

// ---------- PRNG berbiji (hasil selalu sama) ----------
let seed = 20261026;
function rnd() { seed |= 0; seed = (seed + 0x6D2B79F5) | 0; let t = Math.imul(seed ^ (seed >>> 15), 1 | seed); t = (t + Math.imul(t ^ (t >>> 7), 61 | t)) ^ t; return ((t ^ (t >>> 14)) >>> 0) / 4294967296; }
function gauss() { return Math.sqrt(-2 * Math.log(1 - rnd())) * Math.cos(2 * Math.PI * rnd()); }
const uni = (a, b) => a + (b - a) * rnd();
const clamp = (v, a, b) => Math.min(b, Math.max(a, v));

// ---------- aturan ESP32 (sama dengan air-purifier-kel5.ino) ----------
const BATAS_DEBU_RINGAN = 35, BATAS_DEBU_BERAT = 100, BATAS_GAS_RINGAN = 3, BATAS_GAS_BERAT = 7;
const PWM_PELAN = 30, PWM_PENUH = 255;
function skalaPWM(v, lo, hi) { const p = clamp((v - lo) / (hi - lo), 0, 1); return Math.trunc(PWM_PELAN + p * (PWM_PENUH - PWM_PELAN)); }
function aturan(debu, gas) {
  if (debu >= BATAS_DEBU_BERAT || gas >= BATAS_GAS_BERAT) return ["Polusi Berat", PWM_PENUH];
  if (debu >= BATAS_DEBU_RINGAN || gas >= BATAS_GAS_RINGAN)
    return ["Polusi Ringan", Math.max(skalaPWM(debu, BATAS_DEBU_RINGAN, BATAS_DEBU_BERAT), skalaPWM(gas, BATAS_GAS_RINGAN, BATAS_GAS_BERAT))];
  return ["Udara Bersih", PWM_PELAN];
}

// ---------- rencana per hari ----------
const HARI = Math.ceil((N * STEP) / 86400) + 2;
const hari = [];
for (let d = 0; d < HARI; d++) {
  const jenis = rnd();
  const cuaca = jenis < 0.25 ? "hujan" : jenis < 0.85 ? "normal" : "terik";
  const kabut = d === 4 ? uni(1.0, 1.4) : (rnd() < 0.08 ? uni(0.6, 1.0) : 0);   // hari berasap/kabut polusi
  const events = [];
  const tambah = (tipe, jam, durMenit, kuat) => events.push({ tipe, mulai: jam * 60, selesai: jam * 60 + durMenit, kuat });
  // memasak (gas LPG/tumis -> debu + CO)
  [[6.5, 0.8], [12, 0.7], [18.5, 0.9]].forEach(([j, p]) => {
    if (rnd() < p) tambah("masak", j + uni(-0.5, 0.5), uni(15, 45), uni(0.5, 1.6));
  });
  if (rnd() < 0.5) tambah("bersih", uni(8, 17), uni(5, 20), uni(0.6, 1.6));          // menyapu / bersih-bersih
  if (rnd() < 0.18) tambah("rokok", uni(9, 22), uni(10, 30), uni(0.7, 1.4));          // asap rokok
  if (rnd() < 0.15) tambah("obat_nyamuk", uni(18, 22), uni(60, 180), uni(0.6, 1.2));  // obat nyamuk bakar / dupa
  if (rnd() < 0.2) tambah("knalpot", uni(6, 20), uni(5, 20), uni(0.7, 1.5));          // asap kendaraan masuk
  if (rnd() < 0.5) tambah("jendela", uni(7, 16), uni(60, 240), uni(0.5, 1.0));        // jendela dibuka
  // AC: siang atau malam
  const ac = rnd() < 0.65 ? (rnd() < 0.5 ? [13, 17] : [21.5, 29.5]) : null;
  hari.push({ cuaca, kabut, events, ac, offsetSuhu: gauss() * 0.7 });
}

// ---------- gangguan alat (ESP32 mati) ----------
const outage = [];
for (let i = 0; i < 4; i++) { const s = Math.floor(uni(0.05, 0.95) * N * STEP / 60); outage.push([s, s + Math.floor(uni(20, 90))]); }
const sedangMati = (menit) => outage.some(([a, b]) => menit >= a && menit < b);

// ---------- simulasi ----------
const fmtWIB = (ms) => new Date(ms + 7 * 3600 * 1000).toISOString().slice(0, 19).replace("T", " ");
let debu = 12, co = 0.5, suhu = 27, pwm = PWM_PELAN;
let dhtMati = 0;
const rows = [];
let langkah = 0;

while (rows.length < N) {
  const t = START + langkah * STEP * 1000;
  const menitHari = (langkah * STEP / 60) % 1440;
  const jam = menitHari / 60;
  const hr = hari[Math.floor(langkah * STEP / 86400)];
  const hujan = hr.cuaca === "hujan", terik = hr.cuaca === "terik";

  // latar belakang luar ruangan
  const jamSibuk = (jam > 6 && jam < 9) || (jam > 16 && jam < 19) ? 1 : 0;
  let debuLuar = 14 + 10 * jamSibuk + (hujan ? -6 : 0) + (terik ? 6 : 0) + hr.kabut * 90;
  let coLuar = 0.4 + 0.5 * jamSibuk + hr.kabut * 1.2;

  // sumber dalam ruangan
  let srcDebu = 0, srcCO = 0, jendela = false, masak = false;
  for (const e of hr.events) {
    if (menitHari < e.mulai || menitHari >= e.selesai) continue;
    const k = e.kuat;
    if (e.tipe === "masak") { srcDebu += 9 * k; srcCO += 1.0 * k; masak = true; }
    if (e.tipe === "bersih") { srcDebu += 26 * k; }
    if (e.tipe === "rokok") { srcDebu += 32 * k; srcCO += 0.6 * k; }
    if (e.tipe === "obat_nyamuk") { srcDebu += 7 * k; srcCO += 0.25 * k; }
    if (e.tipe === "knalpot") { srcDebu += 7 * k; srcCO += 2.0 * k; }
    if (e.tipe === "jendela") jendela = true;
  }
  srcDebu *= 1.35; srcCO *= 1.35;
  // jendela terbuka: ruangan mengikuti udara luar
  const bgDebu = jendela ? debuLuar : debuLuar * 0.35 + 4;
  const bgCO = jendela ? coLuar : coLuar * 0.5 + 0.1;

  // dinamika (kipas membersihkan lebih cepat saat pwm tinggi)
  const kipas = (pwm - PWM_PELAN) / (PWM_PENUH - PWM_PELAN);
  const kAlami = jendela ? 0.08 : 0.03;
  debu += srcDebu + (kAlami + 0.11 * kipas) * (bgDebu - debu) + gauss() * 0.6;
  co += srcCO + (0.05 + 0.08 * kipas) * (bgCO - co) + gauss() * 0.03;
  debu = clamp(debu, 1, 900);
  co = clamp(co, 0.05, 40);

  // suhu & kelembapan
  const acAktif = hr.ac && ((hr.ac[0] <= jam && jam < hr.ac[1]) || (hr.ac[1] > 24 && jam + 24 < hr.ac[1]));
  let suhuTarget = 27.3 + 3.2 * Math.sin(2 * Math.PI * (jam - 9) / 24) + hr.offsetSuhu + (hujan ? -1.8 : 0) + (terik ? 1.8 : 0) + (masak ? 1.2 : 0);
  if (acAktif) suhuTarget = Math.min(suhuTarget, 24.2 + gauss() * 0.2);
  suhu += 0.08 * (suhuTarget - suhu);
  let lembap = 74 - 2.4 * (suhu - 26) + (hujan ? 13 : 0) + (terik ? -6 : 0) + (acAktif ? -9 : 0) + (masak ? 4 : 0);
  lembap = clamp(lembap + gauss() * 1.0, 28, 96);

  // pembacaan sensor (dengan efek silang & noise)
  let debuUkur = debu * (1 + 0.005 * Math.max(0, lembap - 70)) + gauss() * (1.5 + 0.03 * debu);
  if (rnd() < 0.003) debuUkur += uni(15, 90);                                   // lonjakan acak sesaat
  let coUkur = co * (1 + 0.006 * (lembap - 60) - 0.004 * (suhu - 27)) + gauss() * 0.12;
  debuUkur = Math.round(clamp(debuUkur, 0, 1000) * 10) / 10;
  coUkur = Math.round(clamp(coUkur, 0, 2000) * 10) / 10;

  // kontrol kipas oleh ESP32 (aturan sama dengan kode alat)
  const [status, pwmBaru] = aturan(debuUkur, coUkur);
  pwm = pwmBaru;

  // DHT22 kadang gagal baca (sel kosong)
  if (dhtMati > 0) dhtMati--; else if (rnd() < 0.003) dhtMati = Math.floor(uni(1, 4));
  const dhtOk = dhtMati === 0;
  const s = dhtOk ? (Math.round((suhu + gauss() * 0.2) * 10) / 10).toFixed(1) : "";
  const h = dhtOk ? (Math.round(lembap * 10) / 10).toFixed(1) : "";

  if (!sedangMati(Math.floor(langkah * STEP / 60))) {
    rows.push(`${fmtWIB(t)},${debuUkur.toFixed(1)},${coUkur.toFixed(1)},${s},${h},${status},${pwmBaru}`);
  }
  langkah++;
}

fs.writeFileSync("dataset_air_purifier_10000.csv", "waktu,debu,gas,suhu,kelembapan,status,pwm\n" + rows.join("\n") + "\n");

// ---------- ringkasan ----------
const cnt = {}; let kosong = 0;
rows.forEach(r => { const c = r.split(","); cnt[c[5]] = (cnt[c[5]] || 0) + 1; if (c[3] === "") kosong++; });
console.log("Baris:", rows.length, "| periode:", rows[0].slice(0, 19), "->", rows[rows.length - 1].slice(0, 19));
console.log("Distribusi status:", Object.entries(cnt).map(([k, v]) => `${k} ${(v / rows.length * 100).toFixed(1)}%`).join(" | "));
console.log("Baris suhu/kelembapan kosong:", kosong);
