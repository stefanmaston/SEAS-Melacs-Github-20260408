import fs from "node:fs";
import net from "node:net";
import path from "node:path";
import crypto from "node:crypto";

const file = process.env.MELACS_BOARDS || "/var/lib/melacs/boards.json";

// Kontorets DietPi (192.168.68.61) ska anpassas och bli SEAS central.
// Tills dess visas Lilläng SEAS på hemmalådan i den rollen.
const DEFAULTS = [
  {
    id: "seas-central",
    name: "SEAS central",
    kind: "Lilläng SEAS",
    detail: "övervakar lokala nät",
    host: "192.168.50.60",
    port: 80,
    builtin: true,
  },
  {
    id: "seas-edge",
    name: "SEAS",
    kind: "Rock 5B",
    detail: "DietPi",
    host: "192.168.50.60",
    port: 80,
    builtin: true,
  },
  {
    id: "melacs7",
    name: "Melacs7",
    kind: "PIC32",
    detail: "I/O-slav",
    host: "192.168.1.160",
    port: 502,
    builtin: true,
  },
  {
    id: "challenger",
    name: "Challenger node",
    kind: "RP2350",
    detail: "WiFi I/O",
    host: "192.168.50.22",
    port: 502,
    builtin: true,
  },
];

const KINDS = ["Rock 5B", "Melacs7", "Challenger", "Annan"];

function cleanText(value, max) {
  const text = String(value || "").replace(/\s+/g, " ").trim();
  if (!text || text.length > max) return "";
  if (/[\u0000-\u001f]/.test(text)) return "";
  return text;
}

function cleanHost(value) {
  const text = String(value || "").trim();
  if (!/^[A-Za-z0-9][A-Za-z0-9._-]{0,63}$/.test(text)) return "";
  return text;
}

function cleanPort(value, fallback) {
  const n = Number(value);
  if (!Number.isInteger(n) || n < 1 || n > 65535) return fallback;
  return n;
}

function load() {
  let saved = [];
  try {
    const parsed = JSON.parse(fs.readFileSync(file, "utf8"));
    if (Array.isArray(parsed.boards)) saved = parsed.boards;
  } catch {
    saved = [];
  }
  const byId = new Map(saved.filter((item) => item && item.id).map((item) => [item.id, item]));
  const builtins = DEFAULTS.map((board) => {
    const edited = byId.get(board.id) || {};
    let name = cleanText(edited.name, 48) || board.name;
    if (board.id === "seas-edge" && name === "SEAS edge") name = board.name;
    const detail = edited.detail === undefined
      ? board.detail
      : (cleanText(edited.detail, 48) || board.detail);
    return {
      ...board,
      name,
      detail,
      host: cleanHost(edited.host) || board.host,
      port: cleanPort(edited.port, board.port),
      builtin: true,
    };
  });
  const custom = saved
    .filter((item) => item && !DEFAULTS.some((board) => board.id === item.id))
    .map((item) => ({
      id: String(item.id),
      name: cleanText(item.name, 48),
      kind: KINDS.includes(item.kind) ? item.kind : "Annan",
      detail: cleanText(item.detail, 48),
      host: cleanHost(item.host),
      port: cleanPort(item.port, 502),
      builtin: false,
    }))
    .filter((item) => item.name && item.host);
  return [...builtins, ...custom];
}

function save(boards) {
  fs.mkdirSync(path.dirname(file), { recursive: true, mode: 0o755 });
  const tmp = `${file}.tmp`;
  fs.writeFileSync(tmp, `${JSON.stringify({ boards }, null, 2)}\n`, { mode: 0o644 });
  fs.renameSync(tmp, file);
}

export function challengerEndpoint() {
  const board = load().find((item) => item.id === "challenger");
  return {
    host: board?.host || process.env.CHALLENGER_HOST || "192.168.50.22",
    port: board?.port || Number(process.env.CHALLENGER_PORT || 502),
  };
}

function probe(host, port) {
  return new Promise((resolve) => {
    const socket = net.connect({ host, port });
    const timer = setTimeout(() => {
      socket.destroy();
      resolve(false);
    }, 700);
    socket.once("connect", () => {
      clearTimeout(timer);
      socket.end();
      resolve(true);
    });
    socket.once("error", () => {
      clearTimeout(timer);
      resolve(false);
    });
  });
}

export async function listBoards() {
  const boards = load();
  return Promise.all(boards.map(async (board) => {
    if (board.builtin && board.id !== "seas-central") return { ...board, link: null };
    return { ...board, link: await probe(board.host, board.port) };
  }));
}

export function addBoard(body) {
  const name = cleanText(body.name, 48);
  const host = cleanHost(body.host);
  const kind = KINDS.includes(body.kind) ? body.kind : "";
  const detail = cleanText(body.detail, 48);
  const port = cleanPort(body.port, 502);
  if (!name) return { error: "Ange ett namn." };
  if (!kind) return { error: "Välj en typ." };
  if (!host) return { error: "Ange en adress, till exempel 192.168.50.30." };
  const boards = load();
  if (boards.length >= 24) return { error: "Högst 24 kretskort i schemat." };
  const board = {
    id: `b${crypto.randomBytes(4).toString("hex")}`,
    name,
    kind,
    detail,
    host,
    port,
    builtin: false,
  };
  boards.push(board);
  save(boards);
  return { board };
}

export function updateBoard(id, body) {
  const boards = load();
  const index = boards.findIndex((item) => item.id === id);
  if (index < 0) return { error: "Kortet finns inte." };
  const current = boards[index];
  const name = body.name === undefined ? current.name : cleanText(body.name, 48);
  const host = body.host === undefined ? current.host : cleanHost(body.host);
  const detail = body.detail === undefined ? current.detail : cleanText(body.detail, 48);
  const port = body.port === undefined ? current.port : cleanPort(body.port, 0);
  if (!name) return { error: "Ange ett namn." };
  if (!host) return { error: "Ange en giltig adress." };
  if (!port) return { error: "Port ska vara 1–65535." };
  boards[index] = { ...current, name, host, detail, port };
  save(boards);
  return { board: boards[index] };
}

export function removeBoard(id) {
  const boards = load();
  const board = boards.find((item) => item.id === id);
  if (!board) return { error: "Kortet finns inte." };
  if (board.builtin) return { error: "De fasta korten tas inte bort. Ändra namn eller adress i stället." };
  save(boards.filter((item) => item.id !== id));
  return { ok: true };
}

function readBody(req) {
  return new Promise((resolve, reject) => {
    const chunks = [];
    req.on("data", (chunk) => chunks.push(chunk));
    req.on("end", () => {
      const raw = Buffer.concat(chunks).toString("utf8");
      if (!raw) {
        resolve({});
        return;
      }
      try {
        resolve(JSON.parse(raw));
      } catch (err) {
        reject(err);
      }
    });
    req.on("error", reject);
  });
}

function send(res, status, payload) {
  res.statusCode = status;
  res.setHeader("Content-Type", "application/json; charset=utf-8");
  res.setHeader("Cache-Control", "no-store");
  res.end(JSON.stringify(payload));
}

export async function handleBoards(req, res, session) {
  const url = new URL(req.url || "/", "http://127.0.0.1");
  const id = decodeURIComponent(url.pathname.replace(/^\/api\/boards\/?/, ""));
  const canWrite = session.role === "operator" || session.role === "admin" || session.role === "service";
  if (req.method === "GET" && !id) {
    send(res, 200, { boards: await listBoards() });
    return;
  }
  if (!canWrite) {
    send(res, 403, { error: "Du får bara läsa anläggningen." });
    return;
  }
  try {
    if (req.method === "POST" && !id) {
      const result = addBoard(await readBody(req));
      send(res, result.error ? 400 : 200, result.error ? { error: result.error } : { board: result.board });
      return;
    }
    if (req.method === "PATCH" && id) {
      const result = updateBoard(id, await readBody(req));
      send(res, result.error ? 400 : 200, result.error ? { error: result.error } : { board: result.board });
      return;
    }
    if (req.method === "DELETE" && id) {
      const result = removeBoard(id);
      send(res, result.error ? 400 : 200, result.error ? { error: result.error } : { ok: true });
      return;
    }
  } catch {
    send(res, 400, { error: "Begäran kunde inte läsas." });
    return;
  }
  send(res, 405, { error: "Metoden stöds inte." });
}
