import { spawn } from "child_process";
import path from "path";
import { fileURLToPath } from "url";
import { listPous, setSafety } from "../pou.mjs";

const root = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "../../sd_pack");
const compiler = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "../../tools/compile_protect.py");

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
        const pous = setSafety(root, body.path, Boolean(body.safetyRelated));
        send(res, 200, pous);
      } catch (error) {
        send(res, 400, { error: error.message });
      }
      return;
    }
    if (url.pathname === "/api/compile" && req.method === "POST") {
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
        const marked = listPous(root).filter((pou) => pou.safetyRelated).length;
        send(res, 200, { bytes: hex.length / 2, marked, hex });
      });
      return;
    }
    next();
  });
}
