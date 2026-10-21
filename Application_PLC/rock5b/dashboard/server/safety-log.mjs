import fs from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";

export const SAFETY_CODES = {
  1: "Start",
  2: "Skyddsbild giltig",
  3: "Skyddsbild saknas",
  4: "Skyddsbild fel",
  5: "Master borta",
  6: "Master tillbaka",
  7: "Safe mode",
  9: "Spärr",
  10: "Förregling",
};

const header = "TimeStamp,Seq,Code,Detail\n";

function pad(n) {
  return String(Number(n) || 0).padStart(2, "0");
}

export function formatSafetyLine(event) {
  const stamp = `${event.year}-${pad(event.month)}-${pad(event.day)} ${pad(event.hour)}:${pad(event.minute)}:${pad(event.second)}`;
  return `${stamp},${event.seq},${event.code},${event.detail}\n`;
}

function readLastSeq(filePath) {
  if (!fs.existsSync(filePath)) return 0;
  const text = fs.readFileSync(filePath, "utf8");
  let seq = 0;
  for (const line of text.split("\n")) {
    const parts = line.split(",");
    if (parts.length < 4 || parts[0] === "TimeStamp") continue;
    const n = Number(parts[1]);
    if (Number.isFinite(n) && n > 0) seq = n;
  }
  return seq;
}

export function createSafetyLog(filePath) {
  fs.mkdirSync(path.dirname(filePath), { recursive: true });
  let last = readLastSeq(filePath);

  return {
    filePath,
    lastSeq() {
      return last;
    },
    store(event) {
      if (!event || !event.seq) return 0;
      if (event.seq === last) return last;
      if (last !== 0 && event.seq < last && last - event.seq < 32768) return event.seq;
      const line = formatSafetyLine(event);
      const size = fs.existsSync(filePath) ? fs.statSync(filePath).size : 0;
      if (size === 0) fs.appendFileSync(filePath, header);
      fs.appendFileSync(filePath, line);
      const fd = fs.openSync(filePath, "r+");
      fs.fsyncSync(fd);
      fs.closeSync(fd);
      last = event.seq;
      return last;
    },
    rows() {
      if (!fs.existsSync(filePath)) return [];
      const text = fs.readFileSync(filePath, "utf8");
      const rows = [];
      for (const line of text.split("\n")) {
        if (!line || line.startsWith("TimeStamp")) continue;
        const [stamp, seq, code, detail] = line.split(",");
        const codeN = Number(code);
        rows.push({
          TimeStamp: stamp,
          seq: Number(seq),
          code: codeN,
          detail: Number(detail),
          text: SAFETY_CODES[codeN] || `Kod ${code}`,
        });
      }
      return rows.slice(-80);
    },
  };
}

const defaultPath = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "../data/MELACS.SAF");
let shared;

export function sharedSafetyLog() {
  if (!shared) shared = createSafetyLog(defaultPath);
  return shared;
}
