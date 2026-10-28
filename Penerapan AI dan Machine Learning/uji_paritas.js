// Uji paritas: jalankan kode C++ (ai_peringatan.h + model_rf_peringatan.h) lewat transformasi sederhana ke JS,
// lalu bandingkan peluangnya dengan sklearn. Dipakai karena tidak ada compiler C++ di PC ini.
const fs = require("fs"), vm = require("vm");

function keJS(src) {
  return src
    .replace(/^#pragma.*$/gm, "").replace(/^#include.*$/gm, "").replace(/\/\/.*$/gm, "")
    .replace(/^#define\s+(\w+)\s+(\S+)\s*$/gm, (_, n, v) => `const ${n} = ${v.replace(/f$/, "")};`)
    .replace(/float votes\[2\] = \{0, 0\};/g, "let votes = [0, 0];")
    .replace(/(?:static\s+)?(?:inline\s+)?\b(?:void|bool|float|int)\s+(\w+)\s*\(([^)]*)\)\s*\{/g,
      (_, n, p) => `function ${n}(${p.replace(/\bconst\s+/g, "").replace(/\b(?:float|int)\s*\*?\s*/g, "")}) {`)
    .replace(/^\s*(?:float|int)\s+(\w+)\[(\w+)\];/gm, "let $1 = new Array($2).fill(0);")
    .replace(/\bfor\s*\(int /g, "for (let ")
    .replace(/^(\s*)(?:float|int|bool)\s+(\w+)\s*=/gm, "$1let $2 =")
    .replace(/\(float\)/g, "")
    .replace(/(\d+\.?\d*)f\b/g, "$1");
}

const kode = keJS(fs.readFileSync("hasil_peringatan/model_rf_peringatan.h", "utf8")) + "\n" +
             keJS(fs.readFileSync("ai_peringatan.h", "utf8")) +
             "\n({ aiReset, aiTambahMenit, aiSiap, aiHitungPeluang, AI_AMBANG_DEFAULT, AI_JUMLAH_POHON });";
const api = vm.runInNewContext(kode, { Math });

const baris = fs.readFileSync("hasil_peringatan/uji_paritas.csv", "utf8").trim().split(/\r?\n/);
const kol = baris[0].split(",");
let maks = 0, cocokAlarm = 0, n = 0;
for (const b of baris.slice(1)) {
  const v = Object.fromEntries(b.split(",").map((x, i) => [kol[i], x]));
  api.aiReset();
  for (let i = 0; i < 6; i++) api.aiTambahMenit(+v[`debu${i}`], +v[`gas${i}`], +v[`suhu${i}`], +v[`lembap${i}`]);
  if (!api.aiSiap()) throw new Error("aiSiap() seharusnya true setelah 6 menit");
  const pe = api.aiHitungPeluang(+v.sev5), py = +v.peluang_python;
  maks = Math.max(maks, Math.abs(pe - py));
  if ((pe >= api.AI_AMBANG_DEFAULT) === (py >= api.AI_AMBANG_DEFAULT)) cocokAlarm++;
  n++;
}
api.aiReset();
for (let i = 0; i < 5; i++) api.aiTambahMenit(10, 0.5, 27, 70);
console.log("aiSiap() setelah 5 menit (harus false):", api.aiSiap());
console.log(`Contoh: ${n} | selisih peluang terbesar C++ vs sklearn: ${maks.toExponential(2)} | keputusan alarm sama: ${cocokAlarm}/${n}`);
