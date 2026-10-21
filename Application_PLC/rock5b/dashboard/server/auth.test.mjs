import assert from "node:assert/strict";
import fs from "node:fs";
import os from "node:os";
import path from "node:path";
import { Readable } from "node:stream";
import test from "node:test";
import { fileURLToPath } from "node:url";

const here = path.dirname(fileURLToPath(import.meta.url));
const home = fs.mkdtempSync(path.join(os.tmpdir(), "melacs-auth-"));
process.env.MELACS_HOME = home;
process.env.MELACS_SERVICE_PASSWORD = "TEST-PASS-WORD-1234";
fs.writeFileSync(path.join(home, "plant-id"), fs.readFileSync(path.resolve(here, "../.license/plant-id.txt"), "utf8"));

const { ensureAuth, readSession, routeProtected } = await import("./auth.mjs");
const license = fs.readFileSync(path.resolve(here, "../.license/license-code.txt"), "utf8").trim();

function mockRes() {
  return {
    headersSent: false,
    writableEnded: false,
    status: 0,
    headers: {},
    body: "",
    writeHead(status, headers) {
      this.status = status;
      this.headers = headers || {};
      this.headersSent = true;
    },
    end(body) {
      this.body = body || "";
      this.writableEnded = true;
    },
    json() {
      return JSON.parse(this.body || "{}");
    },
  };
}

function mockReq(method, url, body, cookie) {
  const req = Readable.from(body ? [Buffer.from(body)] : []);
  req.method = method;
  req.url = url;
  req.headers = cookie ? { cookie } : {};
  req.socket = { remoteAddress: "127.0.0.1" };
  return req;
}

async function call(method, url, body, cookie) {
  const req = mockReq(method, url, body, cookie);
  const res = mockRes();
  const done = await routeProtected(req, res);
  return { done, res };
}

test("servicekonto loggar in och kan inte tas bort", async () => {
  await ensureAuth();
  const denied = await call("GET", "/api/live");
  assert.equal(denied.res.status, 401);

  const bad = await call("POST", "/api/session", JSON.stringify({ name: "maston", password: "fel" }));
  assert.equal(bad.res.status, 401);

  const ok = await call("POST", "/api/session", JSON.stringify({ name: "Maston", password: "TEST-PASS-WORD-1234" }));
  assert.equal(ok.res.status, 200);
  assert.equal(ok.res.json().role, "service");
  const cookie = ok.res.headers["set-cookie"].split(";")[0];

  const session = await call("GET", "/api/session", "", cookie);
  assert.equal(session.res.json().name, "maston");
  const req = mockReq("GET", "/api/session", "", cookie);
  assert.equal(readSession(req).role, "service");

  const removed = await call("DELETE", "/api/users?name=maston", "", cookie);
  assert.equal(removed.res.status, 403);
  const rootGone = await call("DELETE", "/api/users?name=root", "", cookie);
  assert.equal(rootGone.res.status, 403);
  const shared = await call("POST", "/api/session", JSON.stringify({ name: "root", password: "seas" }));
  assert.equal(shared.res.status, 200);
  assert.equal(shared.res.json().role, "admin");

  const created = await call(
    "POST",
    "/api/users",
    JSON.stringify({ name: "anna", password: "hemligt1", role: "viewer" }),
    cookie,
  );
  assert.equal(created.res.status, 200);
  const anna = await call("POST", "/api/session", JSON.stringify({ name: "anna", password: "hemligt1" }));
  const annaCookie = anna.res.headers["set-cookie"].split(";")[0];
  const command = await call("POST", "/api/command", "{}", annaCookie);
  assert.equal(command.res.status, 403);
});

test("inloggad användare når FUXA-fliken", async () => {
  await ensureAuth();
  const locked = await call("GET", "/fuxa/");
  assert.equal(locked.res.status, 401);
  assert.equal(locked.done, true);

  const ok = await call("POST", "/api/session", JSON.stringify({ name: "Maston", password: "TEST-PASS-WORD-1234" }));
  const cookie = ok.res.headers["set-cookie"].split(";")[0];
  const open = await call("GET", "/fuxa/", "", cookie);
  assert.equal(open.done, false);
  assert.equal(open.res.status, 0);
});

test("licenskoden gäller bara den här anläggningen", async () => {
  const req = mockReq("GET", "/api/session");
  req.headers.cookie = (await call("POST", "/api/session", JSON.stringify({ name: "maston", password: "TEST-PASS-WORD-1234" }))).res.headers["set-cookie"].split(";")[0];
  const cookie = req.headers.cookie;
  const wrong = await call("POST", "/api/license", JSON.stringify({ code: "inte-en-kod" }), cookie);
  assert.equal(wrong.res.status, 400);
  const right = await call("POST", "/api/license", JSON.stringify({ code: license }), cookie);
  assert.equal(right.res.status, 200);
  assert.equal(right.res.json().license, true);
  const blocked = await call("POST", "/api/openplc", "{}", cookie.replace("maston", "maston"));
  assert.notEqual(blocked.res.status, 403);
});
