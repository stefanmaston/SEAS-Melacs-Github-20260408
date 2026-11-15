import { spawn } from "child_process";
import path from "path";
import { fileURLToPath } from "url";
import { listPous, setLocal, setSafety } from "../pou.mjs";

const root = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "../../sd_pack");
const protectCompiler = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "../../tools/compile_protect.py");
const localCompiler = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "../../tools/compile_local.py");

function send(res, status, body) {
  const raw = JSON.stringify(body);
  res.statusCode = status;
  res.setHeader("content-type", "application/json");
  res.end(raw);
}

async function readJson(req) {
  const chunks = [];
  for await (const chunk of req) {
    chunks.push(chunk);
  }
  if (chunks.length === 0) {
    return {};
  }
  return JSON.parse(Buffer.concat(chunks).toString("utf8"));
}

function runCompiler(compiler, res, countMarked) {
  const child = spawn("python3", [compiler, root], { stdio: ["ignore", "pipe", "pipe"] });
  let out = "";
  let err = "";
  child.stdout.on("data", (chunk) => {
    out += chunk;
  });
  child.stderr.on("data", (chunk) => {
    err += chunk;
  });
  child.on("close", (code) => {
    if (code !== 0) {
      send(res, 400, { error: err.trim() || "kompileringen misslyckades" });
      return;
    }
    const hex = out.trim();
    send(res, 200, { bytes: hex.length / 2, marked: countMarked(), hex });
  });
}

export function attachEditor(middlewares) {
  middlewares.use(async (req, res, next) => {
    const url = new URL(req.url, "http://editor.local");
    if (url.pathname === "/api/pous" && req.method === "GET") {
      send(res, 200, listPous(root));
      return;
    }
    if (url.pathname === "/api/pous" && req.method === "POST") {
      try {
        const body = await readJson(req);
        let pous;
        if (Object.prototype.hasOwnProperty.call(body, "localRelated")) {
          pous = setLocal(root, body.path, Boolean(body.localRelated));
        } else {
          pous = setSafety(root, body.path, Boolean(body.safetyRelated));
        }
        send(res, 200, pous);
      } catch (error) {
        send(res, 400, { error: error.message });
      }
      return;
    }
    if (url.pathname === "/api/compile" && req.method === "POST") {
      runCompiler(protectCompiler, res, () => listPous(root).filter((pou) => pou.safetyRelated).length);
      return;
    }
    if (url.pathname === "/api/compile-local" && req.method === "POST") {
      runCompiler(localCompiler, res, () => listPous(root).filter((pou) => pou.localRelated).length);
      return;
    }
    next();
  });
}
