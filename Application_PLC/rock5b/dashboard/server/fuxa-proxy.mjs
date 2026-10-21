import http from "node:http";

const fuxaHost = process.env.MELACS_FUXA_HOST || "127.0.0.1";
const fuxaPort = Number(process.env.MELACS_FUXA_PORT || 1881);

export function fuxaPath(url) {
  const pathOnly = (url || "/").split("?")[0];
  return pathOnly === "/fuxa" || pathOnly.startsWith("/fuxa/");
}

function pathOnlyOf(url) {
  return (url || "/").split("?")[0];
}

function refererIsFuxa(req) {
  const referer = String(req.headers?.referer || req.headers?.referrer || "");
  return /\/fuxa(?:\/|\?|$)/.test(referer);
}

export function fuxaDelegated(req) {
  const pathOnly = pathOnlyOf(req.url);
  if (fuxaPath(req.url)) return true;
  if (pathOnly === "/socket.io" || pathOnly.startsWith("/socket.io/")) return true;
  return pathOnly.startsWith("/api/") && refererIsFuxa(req);
}

export function fuxaUpstreamPath(url) {
  const raw = url || "/";
  const query = raw.includes("?") ? raw.slice(raw.indexOf("?")) : "";
  const pathOnly = raw.split("?")[0];
  if (pathOnly === "/fuxa") return `/${query}`;
  if (pathOnly.startsWith("/fuxa/")) return `${pathOnly.slice("/fuxa".length)}${query}`;
  return raw;
}

export function redirectFuxaRoot(req, res) {
  const pathOnly = pathOnlyOf(req.url);
  if (pathOnly !== "/fuxa") return false;
  const query = (req.url || "").includes("?") ? req.url.slice(req.url.indexOf("?")) : "";
  res.writeHead(302, { location: `/fuxa/${query}`, "cache-control": "no-store" });
  res.end();
  return true;
}

function prefixLocation(value) {
  let location = String(value)
    .replace(/^https?:\/\/127\.0\.0\.1:\d+/i, "")
    .replace(/^https?:\/\/localhost:\d+/i, "");
  if (location.startsWith("/") && !location.startsWith("/fuxa/") && location !== "/fuxa") {
    location = `/fuxa${location}`;
  }
  return location;
}

function frameHeaders(pres) {
  const headers = { ...pres.headers };
  delete headers["transfer-encoding"];
  delete headers.connection;
  delete headers["x-frame-options"];
  if (headers["content-security-policy"]) {
    headers["content-security-policy"] = String(headers["content-security-policy"]).replace(
      /frame-ancestors[^;]*/gi,
      "frame-ancestors 'self'",
    );
  }
  if (headers.location) headers.location = prefixLocation(headers.location);
  return headers;
}

function unavailable(res) {
  if (res.headersSent || res.writableEnded) return;
  res.statusCode = 502;
  res.setHeader("Content-Type", "text/plain; charset=utf-8");
  res.end("FUXA svarade inte på port 1881.");
}

function sendUpstream(res, pres) {
  const type = String(pres.headers["content-type"] || "");
  const headers = frameHeaders(pres);
  if (!type.includes("text/html")) {
    if (!res.headersSent) res.writeHead(pres.statusCode || 502, headers);
    pres.pipe(res);
    return;
  }
  const chunks = [];
  pres.on("data", (chunk) => chunks.push(chunk));
  pres.on("end", () => {
    const body = Buffer.from(
      Buffer.concat(chunks).toString("utf8").replaceAll('<base href="/">', '<base href="/fuxa/">'),
    );
    headers["content-length"] = String(body.length);
    if (!res.headersSent) res.writeHead(pres.statusCode || 502, headers);
    res.end(body);
  });
}

export function proxyFuxa(req, res) {
  const headers = { ...req.headers };
  headers.host = `${fuxaHost}:${fuxaPort}`;
  headers["x-forwarded-proto"] = "http";
  headers["x-forwarded-for"] = req.socket.remoteAddress || "";
  const preq = http.request(
    {
      host: fuxaHost,
      port: fuxaPort,
      method: req.method,
      path: fuxaUpstreamPath(req.url),
      headers,
    },
    (pres) => {
      pres.on("error", () => res.destroy());
      sendUpstream(res, pres);
    },
  );
  preq.on("error", () => unavailable(res));
  req.pipe(preq);
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

export function proxyFuxaUpgrade(req, socket, head) {
  const headers = { ...req.headers };
  headers.host = `${fuxaHost}:${fuxaPort}`;
  delete headers["content-length"];
  delete headers["transfer-encoding"];
  const preq = http.request({
    host: fuxaHost,
    port: fuxaPort,
    method: req.method || "GET",
    path: fuxaUpstreamPath(req.url),
    headers,
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
