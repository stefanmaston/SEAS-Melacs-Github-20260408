import fs from "node:fs";
import http from "node:http";
import https from "node:https";
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

const cockpitPort = Number(process.env.MELACS_COCKPIT_PORT || 9090);

function cockpitPath(url) {
  const pathOnly = (url || "/").split("?")[0];
  return pathOnly === "/console" || pathOnly.startsWith("/console/") || pathOnly.startsWith("/cockpit/");
}

function cockpitHeaders(req) {
  const headers = { ...req.headers };
  headers["x-forwarded-proto"] = "http";
  headers["x-forwarded-for"] = req.socket.remoteAddress || "";
  return headers;
}

function publicHeaders(pres) {
  const headers = { ...pres.headers };
  delete headers["transfer-encoding"];
  delete headers.connection;
  const cookie = headers["set-cookie"];
  if (cookie) {
    const list = Array.isArray(cookie) ? cookie : [cookie];
    headers["set-cookie"] = list.map((item) =>
      item
        .replace(/;\s*Secure/gi, "")
        .replace(/;\s*Path=\/(?=$|;)/i, "; Path=/console")
        .replace(/SameSite=Strict/gi, "SameSite=Lax"),
    );
  }
  if (headers["content-security-policy"]) {
    headers["content-security-policy"] = String(headers["content-security-policy"])
      .replaceAll("https://", "http://")
      .replaceAll("wss://", "ws://");
  }
  return headers;
}

function requestPath(url) {
  return (url || "/").split("?")[0];
}

function isLoginScript(url) {
  return requestPath(url).endsWith("/login.js");
}

function isLoginPage(url) {
  const pathOnly = requestPath(url);
  return pathOnly === "/console" || pathOnly === "/console/" || pathOnly.endsWith("/login") || pathOnly.endsWith("/login.html");
}

// Cockpit reloads the login page 100 ms after a successful login. That wins
// when the shell is still loading and sends the user back to the form.
const cockpitLoginReload =
  "function U(e){let o=window.setTimeout(function(){o=null,window.location.reload(!0)},100);e&&e!=window.location.href&&(window.location=e),window.onbeforeunload=function(){o&&window.clearTimeout(o),o=null}}";
const cockpitLoginStay =
  "function U(e){if(e&&e!=window.location.href){window.location.assign(e);return}window.location.reload()}";

function rewriteLoginJs(body) {
  const text = body.toString("utf8");
  if (!text.includes(cockpitLoginReload)) return body;
  return Buffer.from(text.replaceAll(cockpitLoginReload, cockpitLoginStay));
}

function proxyCockpit(req, res) {
  const chunks = [];
  req.on("data", (chunk) => chunks.push(chunk));
  req.on("end", () => {
    const body = Buffer.concat(chunks);
    const headers = cockpitHeaders(req);
    headers["content-length"] = String(body.length);
    delete headers["transfer-encoding"];
    const loginScript = isLoginScript(req.url);
    const loginPage = isLoginPage(req.url);
    if (loginScript || loginPage) delete headers["accept-encoding"];
    const preq = https.request(
      {
        host: "127.0.0.1",
        port: cockpitPort,
        method: req.method,
        path: req.url,
        headers,
        rejectUnauthorized: false,
      },
      (pres) => {
        pres.on("error", () => res.destroy());
        if (!loginScript && !loginPage) {
          if (!res.headersSent) res.writeHead(pres.statusCode || 502, publicHeaders(pres));
          pres.pipe(res);
          return;
        }
        const out = [];
        pres.on("data", (chunk) => out.push(chunk));
        pres.on("end", () => {
          let rewritten = Buffer.concat(out);
          if (loginScript) rewritten = rewriteLoginJs(rewritten);
          if (loginPage) {
            rewritten = Buffer.from(
              rewritten.toString("utf8").replaceAll('src="cockpit/static/login.js"', 'src="cockpit/static/login.js?melacs=2"'),
            );
          }
          const responseHeaders = publicHeaders(pres);
          responseHeaders["content-length"] = String(rewritten.length);
          responseHeaders["cache-control"] = "no-cache";
          if (!res.headersSent) res.writeHead(pres.statusCode || 502, responseHeaders);
          res.end(rewritten);
        });
      },
    );
    preq.on("error", () => {
      if (!res.headersSent) {
        res.statusCode = 502;
        res.setHeader("Content-Type", "text/plain; charset=utf-8");
      }
      res.end("Cockpit svarade inte");
    });
    preq.end(body);
  });
}

function writeHeaderLines(headers) {
  let out = "";
  for (const [key, value] of Object.entries(headers)) {
    if (value == null) continue;
    const items = Array.isArray(value) ? value : [value];
    for (const item of items) out += `${key}: ${item}\r\n`;
  }
  return out;
}

function proxyCockpitUpgrade(req, socket, head) {
  const headers = cockpitHeaders(req);
  delete headers["content-length"];
  delete headers["transfer-encoding"];
  const preq = https.request({
    host: "127.0.0.1",
    port: cockpitPort,
    method: req.method || "GET",
    path: req.url,
    headers,
    rejectUnauthorized: false,
  });
  const closeBoth = (upstream) => {
    socket.destroy();
    if (upstream) upstream.destroy();
  };
  preq.on("upgrade", (pres, upstream, uphead) => {
    socket.write(`HTTP/1.1 ${pres.statusCode || 101} ${pres.statusMessage || "Switching Protocols"}\r\n`);
    socket.write(writeHeaderLines(pres.headers));
    socket.write("\r\n");
    if (uphead && uphead.length) socket.write(uphead);
    if (head && head.length) upstream.write(head);
    upstream.pipe(socket);
    socket.pipe(upstream);
    upstream.on("error", () => closeBoth(upstream));
    socket.on("error", () => closeBoth(upstream));
    upstream.on("close", () => socket.destroy());
    socket.on("close", () => upstream.destroy());
  });
  preq.on("response", (pres) => {
    socket.end(`HTTP/1.1 ${pres.statusCode || 502} ${pres.statusMessage || "Bad Gateway"}\r\nConnection: close\r\n\r\n`);
    pres.resume();
  });
  preq.on("error", () => socket.destroy());
  preq.end();
}

const server = http.createServer((req, res) => {
  if (cockpitPath(req.url)) {
    proxyCockpit(req, res);
    return;
  }
  dispatch(0, req, res);
});
server.on("upgrade", (req, socket, head) => {
  if (cockpitPath(req.url)) {
    proxyCockpitUpgrade(req, socket, head);
    return;
  }
  socket.destroy();
});
server.listen(listenPort, listenHost, () => {
  const card = `${process.env.MELACS_HOST || "127.0.0.1"}:${process.env.MELACS_PORT || 1502}`;
  console.log(`Melacs dashboard http://${listenHost}:${listenPort} modbus ${card}`);
});
