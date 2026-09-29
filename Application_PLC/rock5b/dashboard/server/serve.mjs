import fs from "node:fs";
import http from "node:http";
import path from "node:path";
import { fileURLToPath } from "node:url";
import { attachPlant } from "./plant.mjs";

const here = path.dirname(fileURLToPath(import.meta.url));
const root = path.resolve(here, "../dist");
const listenHost = process.env.MELACS_WEB_HOST || "0.0.0.0";
const listenPort = Number(process.env.MELACS_WEB_PORT || 80);

const types = {
  ".css": "text/css; charset=utf-8",
  ".html": "text/html; charset=utf-8",
  ".ico": "image/x-icon",
  ".jpeg": "image/jpeg",
  ".jpg": "image/jpeg",
  ".js": "text/javascript; charset=utf-8",
  ".json": "application/json; charset=utf-8",
  ".png": "image/png",
  ".svg": "image/svg+xml",
  ".webp": "image/webp",
  ".woff2": "font/woff2",
};

const handlers = [];
attachPlant({
  use(fn) {
    handlers.push(fn);
  },
});

function insideRoot(file) {
  return file === root || file.startsWith(root + path.sep);
}

function sendFile(res, file) {
  fs.readFile(file, (err, data) => {
    if (err) {
      res.statusCode = 404;
      res.setHeader("Content-Type", "text/plain; charset=utf-8");
      res.end("Not found");
      return;
    }
    const ext = path.extname(file);
    res.statusCode = 200;
    res.setHeader("Content-Type", types[ext] || "application/octet-stream");
    if (ext !== ".html") res.setHeader("Cache-Control", "public, max-age=3600");
    res.end(data);
  });
}

function serveStatic(req, res) {
  let rel = "/";
  try {
    rel = decodeURIComponent(new URL(req.url || "/", "http://127.0.0.1").pathname);
  } catch {
    res.statusCode = 400;
    res.end("Bad request");
    return;
  }
  if (rel.endsWith("/")) rel += "index.html";
  const file = path.resolve(root, `.${rel}`);
  if (!insideRoot(file)) {
    res.statusCode = 403;
    res.end("Forbidden");
    return;
  }
  fs.stat(file, (err, stat) => {
    if (!err && stat.isFile()) {
      sendFile(res, file);
      return;
    }
    sendFile(res, path.join(root, "index.html"));
  });
}

function dispatch(index, req, res) {
  const handler = handlers[index];
  if (!handler) {
    serveStatic(req, res);
    return;
  }
  handler(req, res, () => dispatch(index + 1, req, res));
}

const server = http.createServer((req, res) => dispatch(0, req, res));
server.listen(listenPort, listenHost, () => {
  const card = `${process.env.MELACS_HOST || "127.0.0.1"}:${process.env.MELACS_PORT || 1502}`;
  console.log(`Melacs dashboard http://${listenHost}:${listenPort} modbus ${card}`);
});
