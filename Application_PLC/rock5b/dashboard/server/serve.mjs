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

function cookiePairs(header) {
  const pairs = new Map();
  for (const part of String(header || "").split(";")) {
    const eq = part.indexOf("=");
    if (eq < 0) continue;
    pairs.set(part.slice(0, eq).trim(), part.slice(eq + 1).trim());
  }
  return pairs;
}

function encodeSession(value) {
  return Buffer.from(value, "utf8").toString("hex");
}

function decodeSession(value) {
  if (!/^[0-9a-f]+$/i.test(value) || value.length % 2) return "";
  return Buffer.from(value, "hex").toString("utf8");
}

function cookieHeaderForCockpit(header) {
  const pairs = cookiePairs(header);
  const stored = decodeSession(pairs.get("melacs_session") || "");
  if (stored) return `cockpit=${stored}`;
  const legacy = pairs.get("cockpit");
  if (legacy && legacy !== "deleted") return `cockpit=${legacy}`;
  return "";
}

function cockpitHeaders(req) {
  const headers = { ...req.headers };
  headers["x-forwarded-proto"] = "http";
  headers["x-forwarded-for"] = req.socket.remoteAddress || "";
  const cookie = cookieHeaderForCockpit(headers.cookie);
  if (cookie) headers.cookie = cookie;
  else delete headers.cookie;
  return headers;
}

function rewriteSetCookie(item) {
  const cleaned = String(item).replace(/;\s*Secure/gi, "").replace(/SameSite=Strict/gi, "SameSite=Lax");
  const first = cleaned.split(";")[0];
  const eq = first.indexOf("=");
  const name = eq < 0 ? "" : first.slice(0, eq).trim();
  const value = eq < 0 ? "" : first.slice(eq + 1).trim();
  if (name !== "cockpit") return cleaned.replace(/;\s*Path=\/(?=$|;)/i, "; Path=/console");
  if (!value || value === "deleted") return "melacs_session=; Path=/; Max-Age=0; HttpOnly; SameSite=Lax";
  return `melacs_session=${encodeSession(value)}; Path=/; HttpOnly; SameSite=Lax`;
}

function publicHeaders(pres) {
  const headers = { ...pres.headers };
  delete headers["transfer-encoding"];
  delete headers.connection;
  const cookie = headers["set-cookie"];
  if (cookie) {
    const list = Array.isArray(cookie) ? cookie : [cookie];
    headers["set-cookie"] = list.flatMap((item) => {
      const rewritten = rewriteSetCookie(item);
      if (/^melacs_session=[0-9a-f]/i.test(rewritten)) {
        return [
          rewritten,
          "cockpit=deleted; Path=/console; Max-Age=0; SameSite=Lax",
          "cockpit=deleted; Path=/; Max-Age=0; SameSite=Lax",
        ];
      }
      return [rewritten];
    });
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

// Do not reload until a credentialed probe says the session exists. A reload
// without the cookie is what sends the browser back to the login form.
const cockpitLoginReload =
  "function U(e){let o=window.setTimeout(function(){o=null,window.location.reload(!0)},100);e&&e!=window.location.href&&(window.location=e),window.onbeforeunload=function(){o&&window.clearTimeout(o),o=null}}";
const cockpitLoginImmediate =
  "function U(e){if(e&&e!=window.location.href){window.location.assign(e);return}window.location.reload()}";
const cockpitLoginWait =
  "function U(e){window.setTimeout(function(){if(e&&e!==window.location.href)window.location.assign(e);else window.location.reload()},300)}";
const cockpitLoginSecond =
  "function U(e){window.setTimeout(function(){if(e&&e!==window.location.href)window.location.assign(e);else window.location.reload()},1000)}";
const cockpitLoginStay =
  "function U(e){var n=0;function a(){var x=new XMLHttpRequest;x.open('GET','/console/melacs-session',!0);x.withCredentials=!0;x.onreadystatechange=function(){if(x.readyState!==4)return;if(x.status===204){if(e&&e!==window.location.href)window.location.replace(e);else window.location.replace('/console/');return}if(++n<40)window.setTimeout(a,50)};x.send()}a()}";

function rewriteLoginJs(body) {
  let text = body.toString("utf8");
  text = text.replaceAll(cockpitLoginReload, cockpitLoginStay);
  text = text.replaceAll(cockpitLoginImmediate, cockpitLoginStay);
  text = text.replaceAll(cockpitLoginWait, cockpitLoginStay);
  text = text.replaceAll(cockpitLoginSecond, cockpitLoginStay);
  return Buffer.from(text);
}

const loginTakeover =
  "<script>(function(){var started=false;function hidden(id){var el=document.getElementById(id);return !el||el.hidden||el.getAttribute('hidden')!==null}function begin(event){var button=document.getElementById('login-button');var password=document.getElementById('login-password-input');var user=document.getElementById('login-user-input');if(!button||!password||!user)return;if(!hidden('conversation-group')||!hidden('hostkey-group'))return;var enter=event.type==='keydown'&&(event.key==='Enter'||event.which===13)&&event.target===password;var click=event.type==='click'&&event.target&&event.target.closest&&event.target.closest('#login-button');if(!enter&&!click)return;event.preventDefault();event.stopImmediatePropagation();if(started)return;started=true;button.setAttribute('disabled','true');var form=document.createElement('form');form.method='POST';form.action='/console/melacs-session';function field(name,value){var input=document.createElement('input');input.type='hidden';input.name=name;input.value=value||'';form.appendChild(input)}field('user',user.value);field('password',password.value);document.body.appendChild(form);form.submit()}document.addEventListener('click',begin,true);document.addEventListener('keydown',begin,true)})()</script>";

function rewriteLoginHtml(body) {
  let text = body.toString("utf8").replaceAll('src="cockpit/static/login.js"', 'src="cockpit/static/login.js?melacs=5"');
  if (text.includes("login-user-input") && text.includes("</body>")) text = text.replace("</body>", `${loginTakeover}</body>`);
  return Buffer.from(text);
}

function askCockpit(req, extra) {
  const headers = {
    host: req.headers.host || "127.0.0.1",
    accept: "*/*",
    "x-forwarded-proto": "http",
    "x-forwarded-for": req.socket.remoteAddress || "",
  };
  const cookie = cookieHeaderForCockpit(extra.cookie || "");
  if (cookie) headers.cookie = cookie;
  if (extra.authorization) headers.authorization = extra.authorization;
  return new Promise((resolve) => {
    const preq = https.request(
      {
        host: "127.0.0.1",
        port: cockpitPort,
        method: "GET",
        path: "/console/cockpit/login",
        headers,
        rejectUnauthorized: false,
        timeout: 15000,
      },
      (pres) => {
        pres.resume();
        pres.on("end", () => resolve(pres));
      },
    );
    preq.on("timeout", () => preq.destroy());
    preq.on("error", () => resolve(null));
    preq.end();
  });
}

function liveSessionCookies(pres) {
  const raw = publicHeaders(pres)["set-cookie"] || [];
  const list = Array.isArray(raw) ? raw : [raw];
  const session = list.filter((item) => /^melacs_session=[0-9a-f]/i.test(String(item).split(";")[0]));
  if (!session.length) return [];
  return list.filter((item) => /^melacs_session=/.test(String(item)) || /^cockpit=deleted/.test(String(item)));
}

function sendHtml(res, status, html, cookies) {
  const body = Buffer.from(html);
  const headers = {
    "content-type": "text/html; charset=utf-8",
    "cache-control": "no-store",
    "content-length": String(body.length),
  };
  if (cookies && cookies.length) headers["set-cookie"] = cookies;
  res.writeHead(status, headers);
  res.end(body);
}

const sessionWaitHtml = `<!DOCTYPE html>
<meta charset="utf-8">
<title>Loggar in</title>
<style>body{margin:0;min-height:100vh;display:grid;place-items:center;background:#1b1d21;color:#f2f2f2;font:16px/1.4 sans-serif}p{margin:0}</style>
<p id="status">Loggar in…</p>
<script>window.location.replace("/console/melacs-enter");</script>`;

const sessionFailedHtml = `<!DOCTYPE html>
<meta charset="utf-8">
<title>Inloggning</title>
<style>body{margin:0;min-height:100vh;display:grid;place-items:center;background:#1b1d21;color:#f2f2f2;font:16px/1.4 sans-serif}a{color:#8cb4ff}</style>
<p>Fel användarnamn eller lösenord. <a href="/console/">Försök igen</a></p>`;

function handleMelacsEnter(req, res) {
  askCockpit(req, { cookie: req.headers.cookie || "" }).then((pres) => {
    if (pres && pres.statusCode === 200) {
      res.writeHead(302, { location: "/console/", "cache-control": "no-store" });
      res.end();
      return;
    }
    sendHtml(res, 401, sessionWaitHtml.replace("Loggar in…", "Inloggningen sparades inte i webbläsaren. Ladda om sidan och försök igen.").replace('<script>window.location.replace("/console/melacs-enter");</script>', ""));
  });
}

function handleMelacsSession(req, res) {
  if (req.method === "GET") {
    askCockpit(req, { cookie: req.headers.cookie || "" }).then((pres) => {
      if (!pres) {
        res.writeHead(502, { "content-type": "text/plain; charset=utf-8", "cache-control": "no-store" });
        res.end("Cockpit svarade inte");
        return;
      }
      res.writeHead(pres.statusCode === 200 ? 204 : 401, { "cache-control": "no-store" });
      res.end();
    });
    return;
  }
  if (req.method !== "POST") {
    res.writeHead(405, { allow: "GET, POST", "cache-control": "no-store" });
    res.end();
    return;
  }
  const chunks = [];
  let size = 0;
  req.on("data", (chunk) => {
    size += chunk.length;
    if (size > 4096) {
      req.destroy();
      return;
    }
    chunks.push(chunk);
  });
  req.on("end", () => {
    const params = new URLSearchParams(Buffer.concat(chunks).toString("utf8"));
    const user = params.get("user") || "";
    const password = params.get("password") || "";
    const authorization = `Basic ${Buffer.from(`${user}:${password}\0`, "utf8").toString("base64")}`;
    askCockpit(req, { authorization }).then((pres) => {
      if (!pres) {
        sendHtml(res, 502, sessionFailedHtml.replace("Fel användarnamn eller lösenord.", "Cockpit svarade inte."));
        return;
      }
      const cookies = pres.statusCode === 200 ? liveSessionCookies(pres) : [];
      if (pres.statusCode === 200 && cookies.length) {
        sendHtml(res, 200, sessionWaitHtml, cookies);
        return;
      }
      sendHtml(res, 401, sessionFailedHtml);
    });
  });
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
          if (loginPage) rewritten = rewriteLoginHtml(rewritten);
          const responseHeaders = publicHeaders(pres);
          responseHeaders["content-length"] = String(rewritten.length);
          responseHeaders["cache-control"] = "no-store";
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
  if (requestPath(req.url) === "/console/melacs-enter") {
    handleMelacsEnter(req, res);
    return;
  }
  if (requestPath(req.url) === "/console/melacs-session") {
    handleMelacsSession(req, res);
    return;
  }
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
