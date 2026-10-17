import crypto from "node:crypto";
import fs from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";
import { openplcStart, openplcStatus } from "./openplc.mjs";

const here = path.dirname(fileURLToPath(import.meta.url));
const SERVICE_NAME = "maston";
const SHARED_NAME = "root";
const SHARED_PASSWORD = "seas";
const SESSION_MS = 12 * 60 * 60 * 1000;
const MAX_USERS = 50;
const FAIL_LIMIT = 8;
const FAIL_WINDOW_MS = 10 * 60 * 1000;

const publicKey = crypto.createPublicKey(
  fs.readFileSync(path.join(here, "keys/license-public.pem")),
);

const failures = new Map();

function homeDir() {
  return process.env.MELACS_HOME || path.resolve(here, "../data");
}

function writeJson(file, value) {
  const dir = path.dirname(file);
  fs.mkdirSync(dir, { recursive: true, mode: 0o700 });
  const tmp = `${file}.${process.pid}.tmp`;
  fs.writeFileSync(tmp, `${JSON.stringify(value, null, 2)}\n`, { mode: 0o600 });
  fs.renameSync(tmp, file);
}

function readJson(file, fallback) {
  try {
    return JSON.parse(fs.readFileSync(file, "utf8"));
  } catch {
    return fallback;
  }
}

function scrypt(password, salt) {
  return new Promise((resolve, reject) => {
    crypto.scrypt(password, salt, 32, { N: 16384, r: 8, p: 1 }, (err, key) => {
      if (err) reject(err);
      else resolve(key);
    });
  });
}

async function hashPassword(password) {
  const salt = crypto.randomBytes(16);
  const hash = await scrypt(password, salt);
  return { salt: salt.toString("base64url"), hash: hash.toString("base64url") };
}

let dummy = null;

async function dummyHash() {
  if (!dummy) dummy = await hashPassword("missing-user");
  return dummy;
}

function accountsFile() {
  return path.join(homeDir(), "accounts.json");
}

function serviceFile() {
  return path.join(homeDir(), "service.json");
}

function sessionFile() {
  return path.join(homeDir(), "session.key");
}

function plantFile() {
  return path.join(homeDir(), "plant-id");
}

function licenseFile() {
  return path.join(homeDir(), "license.json");
}

function loadAccounts() {
  const data = readJson(accountsFile(), { users: [] });
  return Array.isArray(data.users) ? data.users : [];
}

function saveAccounts(users) {
  writeJson(accountsFile(), { users });
}

function loadService() {
  return readJson(serviceFile(), null);
}

function sessionKey() {
  const file = sessionFile();
  try {
    return fs.readFileSync(file);
  } catch {
    const key = crypto.randomBytes(32);
    fs.mkdirSync(path.dirname(file), { recursive: true, mode: 0o700 });
    fs.writeFileSync(file, key, { mode: 0o600 });
    return key;
  }
}

export function plantId() {
  const file = plantFile();
  try {
    const id = fs.readFileSync(file, "utf8").trim();
    if (id) return id;
  } catch {
    /* Skapas nedan. */
  }
  const id = crypto.randomUUID();
  fs.mkdirSync(path.dirname(file), { recursive: true, mode: 0o700 });
  fs.writeFileSync(file, `${id}\n`, { mode: 0o600 });
  return id;
}

function makePassword() {
  const alphabet = "23456789ABCDEFGHJKLMNPQRSTUVWXYZ";
  const bytes = crypto.randomBytes(16);
  let raw = "";
  for (const byte of bytes) raw += alphabet[byte % alphabet.length];
  return `${raw.slice(0, 4)}-${raw.slice(4, 8)}-${raw.slice(8, 12)}-${raw.slice(12, 16)}`;
}

export async function ensureAuth() {
  fs.mkdirSync(homeDir(), { recursive: true, mode: 0o700 });
  sessionKey();
  plantId();
  await dummyHash();
  if (!loadService()) {
    const generated = !process.env.MELACS_SERVICE_PASSWORD;
    const password = process.env.MELACS_SERVICE_PASSWORD || makePassword();
    const record = {
      name: SERVICE_NAME,
      role: "service",
      ...(await hashPassword(password)),
    };
    writeJson(serviceFile(), record);
    if (generated) {
      fs.writeFileSync(path.join(homeDir(), "owner-password.txt"), `${password}\n`, { mode: 0o600 });
    }
  }
  const users = loadAccounts().filter((user) => user.name !== SHARED_NAME);
  users.unshift({
    name: SHARED_NAME,
    role: "admin",
    ...(await hashPassword(SHARED_PASSWORD)),
  });
  saveAccounts(users);
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

function signSession(payload) {
  const body = Buffer.from(JSON.stringify(payload)).toString("base64url");
  const sig = crypto.createHmac("sha256", sessionKey()).update(body).digest("base64url");
  return `${body}.${sig}`;
}

function verifyToken(token) {
  const parts = String(token || "").split(".");
  if (parts.length !== 2) return null;
  const expected = crypto.createHmac("sha256", sessionKey()).update(parts[0]).digest("base64url");
  const actual = Buffer.from(parts[1]);
  const wanted = Buffer.from(expected);
  if (actual.length !== wanted.length || !crypto.timingSafeEqual(actual, wanted)) return null;
  try {
    return JSON.parse(Buffer.from(parts[0], "base64url").toString("utf8"));
  } catch {
    return null;
  }
}

function findUser(name) {
  if (name === SERVICE_NAME) return loadService();
  return loadAccounts().find((user) => user.name === name) || null;
}

export function readSession(req) {
  const token = cookiePairs(req.headers.cookie).get("melacs_auth");
  const payload = verifyToken(token);
  if (!payload || payload.exp < Date.now()) return null;
  const user = findUser(payload.name);
  if (!user) return null;
  return publicUser(user);
}

function publicUser(user) {
  return {
    name: user.name,
    role: user.role,
    license: licenseActive(),
    plantId: plantId(),
  };
}

function canControl(session) {
  return session.role === "operator" || session.role === "admin" || session.role === "service";
}

function canAdmin(session) {
  return session.role === "admin" || session.role === "service";
}

function licenseActive() {
  const saved = readJson(licenseFile(), null);
  if (!saved || !saved.code) return false;
  return verifyLicense(saved.code) === null;
}

function verifyLicense(code) {
  const parts = String(code || "").trim().split(".");
  if (parts.length !== 2) return "Licenskoden stämmer inte för den här anläggningen.";
  let body;
  let sig;
  try {
    body = Buffer.from(parts[0], "base64url");
    sig = Buffer.from(parts[1], "base64url");
  } catch {
    return "Licenskoden stämmer inte för den här anläggningen.";
  }
  if (!crypto.verify(null, body, publicKey, sig)) {
    return "Licenskoden stämmer inte för den här anläggningen.";
  }
  let payload;
  try {
    payload = JSON.parse(body.toString("utf8"));
  } catch {
    return "Licenskoden stämmer inte för den här anläggningen.";
  }
  if (payload.product !== "melacs-seas" || payload.openplc !== true || payload.plant !== plantId()) {
    return "Licenskoden stämmer inte för den här anläggningen.";
  }
  return null;
}

function clientKey(req) {
  return req.socket.remoteAddress || "okänd";
}

function blocked(req) {
  const row = failures.get(clientKey(req));
  if (!row) return false;
  if (row.reset < Date.now()) {
    failures.delete(clientKey(req));
    return false;
  }
  return row.count >= FAIL_LIMIT;
}

function noteFailure(req) {
  const key = clientKey(req);
  const row = failures.get(key);
  if (!row || row.reset < Date.now()) {
    failures.set(key, { count: 1, reset: Date.now() + FAIL_WINDOW_MS });
    return;
  }
  row.count += 1;
}

function clearFailure(req) {
  failures.delete(clientKey(req));
}

function sendJson(res, status, payload, cookies) {
  const body = JSON.stringify(payload);
  const headers = {
    "content-type": "application/json; charset=utf-8",
    "cache-control": "no-store",
    "content-length": Buffer.byteLength(body),
  };
  if (cookies) headers["set-cookie"] = cookies;
  res.writeHead(status, headers);
  res.end(body);
}

function readBody(req, limit) {
  return new Promise((resolve, reject) => {
    const chunks = [];
    let size = 0;
    req.on("data", (chunk) => {
      size += chunk.length;
      if (size > limit) {
        reject(new Error("för stor"));
        req.destroy();
        return;
      }
      chunks.push(chunk);
    });
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

function requestPath(url) {
  return (url || "/").split("?")[0];
}

function authCookie(token) {
  return `melacs_auth=${token}; Path=/; HttpOnly; SameSite=Lax; Max-Age=${SESSION_MS / 1000}`;
}

function clearCookie() {
  return "melacs_auth=; Path=/; HttpOnly; SameSite=Lax; Max-Age=0";
}

async function login(name, password) {
  const user = findUser(String(name || "").trim().toLowerCase());
  const material = user || (await dummyHash());
  const salt = Buffer.from(material.salt, "base64url");
  const expected = Buffer.from(material.hash, "base64url");
  const actual = await scrypt(String(password || ""), salt);
  if (!user || actual.length !== expected.length || !crypto.timingSafeEqual(actual, expected)) {
    return null;
  }
  return user;
}

function validName(name) {
  return /^[a-z][a-z0-9-]{1,31}$/.test(name);
}

async function handleSession(req, res) {
  if (req.method === "GET") {
    const session = readSession(req);
    if (!session) {
      sendJson(res, 401, { error: "Logga in krävs." });
      return;
    }
    sendJson(res, 200, session);
    return;
  }
  if (req.method === "DELETE") {
    sendJson(res, 200, { ok: true }, clearCookie());
    return;
  }
  if (req.method !== "POST") {
    sendJson(res, 405, { error: "Metoden stöds inte." });
    return;
  }
  if (blocked(req)) {
    sendJson(res, 429, { error: "För många försök. Vänta och prova igen." });
    return;
  }
  let body;
  try {
    body = await readBody(req, 4096);
  } catch {
    sendJson(res, 400, { error: "Begäran kunde inte läsas." });
    return;
  }
  const user = await login(body.name, body.password);
  if (!user) {
    noteFailure(req);
    sendJson(res, 401, { error: "Fel användarnamn eller lösenord." });
    return;
  }
  clearFailure(req);
  const token = signSession({ name: user.name, exp: Date.now() + SESSION_MS });
  sendJson(res, 200, publicUser(user), authCookie(token));
}

async function handleUsers(req, res, session) {
  if (!canAdmin(session)) {
    sendJson(res, 403, { error: "Bara administratören kan hantera användare." });
    return;
  }
  if (req.method === "GET") {
    const users = [loadService(), ...loadAccounts()]
      .filter(Boolean)
      .map((user) => ({ name: user.name, role: user.role }));
    sendJson(res, 200, { users });
    return;
  }
  if (req.method === "DELETE") {
    const name = new URL(req.url, "http://127.0.0.1").searchParams.get("name") || "";
    if (name === SERVICE_NAME || name === SHARED_NAME) {
      sendJson(res, 403, { error: "Det här kontot kan inte tas bort." });
      return;
    }
    const users = loadAccounts().filter((user) => user.name !== name);
    saveAccounts(users);
    sendJson(res, 200, { ok: true });
    return;
  }
  if (req.method !== "POST") {
    sendJson(res, 405, { error: "Metoden stöds inte." });
    return;
  }
  let body;
  try {
    body = await readBody(req, 4096);
  } catch {
    sendJson(res, 400, { error: "Begäran kunde inte läsas." });
    return;
  }
  const name = String(body.name || "").trim().toLowerCase();
  const password = String(body.password || "");
  const role = body.role;
  if (!validName(name) || name === SERVICE_NAME || name === SHARED_NAME) {
    sendJson(res, 400, { error: "Användarnamnet kan inte användas." });
    return;
  }
  if (password.length < 8) {
    sendJson(res, 400, { error: "Lösenordet måste ha minst 8 tecken." });
    return;
  }
  if (role !== "viewer" && role !== "operator" && role !== "admin") {
    sendJson(res, 400, { error: "Rollen stöds inte." });
    return;
  }
  const users = loadAccounts().filter((user) => user.name !== name);
  if (users.length >= MAX_USERS) {
    sendJson(res, 400, { error: "Anläggningen har redan tillräckligt många användare." });
    return;
  }
  users.push({ name, role, ...(await hashPassword(password)) });
  saveAccounts(users);
  sendJson(res, 200, { ok: true });
}

async function handleLicense(req, res, session) {
  if (!canAdmin(session)) {
    sendJson(res, 403, { error: "Bara administratören kan skriva in licenskoden." });
    return;
  }
  if (req.method !== "POST") {
    sendJson(res, 405, { error: "Metoden stöds inte." });
    return;
  }
  let body;
  try {
    body = await readBody(req, 4096);
  } catch {
    sendJson(res, 400, { error: "Begäran kunde inte läsas." });
    return;
  }
  const code = String(body.code || "").trim();
  const error = verifyLicense(code);
  if (error) {
    sendJson(res, 400, { error });
    return;
  }
  writeJson(licenseFile(), { code });
  sendJson(res, 200, { license: true, plantId: plantId() });
}

async function handleOpenplc(req, res, session) {
  if (req.method === "GET") {
    const status = await openplcStatus();
    sendJson(res, 200, { ...status, license: licenseActive() });
    return;
  }
  if (req.method !== "POST") {
    sendJson(res, 405, { error: "Metoden stöds inte." });
    return;
  }
  if (!canAdmin(session)) {
    sendJson(res, 403, { error: "Bara administratören kan ansluta OpenPLC." });
    return;
  }
  if (!licenseActive()) {
    sendJson(res, 403, { error: "OpenPLC kräver licenskoden som följde med leveransen." });
    return;
  }
  try {
    await openplcStart();
  } catch (err) {
    sendJson(res, 502, { error: err.message || "OpenPLC svarade inte." });
    return;
  }
  const status = await openplcStatus();
  sendJson(res, 200, { ...status, license: true });
}

export async function routeProtected(req, res) {
  const pathOnly = requestPath(req.url);
  if (pathOnly === "/api/session") {
    await handleSession(req, res);
    return true;
  }
  const needsAuth = pathOnly.startsWith("/api/") || pathOnly.startsWith("/console") || pathOnly.startsWith("/cockpit/");
  if (!needsAuth) return false;
  const session = readSession(req);
  if (!session) {
    sendJson(res, 401, { error: "Logga in krävs." });
    return true;
  }
  if ((pathOnly.startsWith("/console") || pathOnly.startsWith("/cockpit/")) && !canAdmin(session)) {
    sendJson(res, 403, { error: "Cockpit kräver administratör." });
    return true;
  }
  if (pathOnly.startsWith("/api/users")) {
    await handleUsers(req, res, session);
    return true;
  }
  if (pathOnly === "/api/license") {
    await handleLicense(req, res, session);
    return true;
  }
  if (pathOnly === "/api/openplc") {
    await handleOpenplc(req, res, session);
    return true;
  }
  if (pathOnly.startsWith("/api/command") && !canControl(session)) {
    sendJson(res, 403, { error: "Du får bara läsa anläggningen." });
    return true;
  }
  return false;
}

export function allowCockpitUpgrade(req) {
  const session = readSession(req);
  return Boolean(session && canAdmin(session));
}
