// Hittar SEAS-utrustning på de lokala näten och skriver in den i schemat.
// En skrivare, en teve eller en främmande dator tas inte med.
import { execFile } from "node:child_process";
import fs from "node:fs";
import http from "node:http";
import net from "node:net";
import { applyDiscovery } from "./boards.mjs";

const MELACS7_OUI = "d8:80:39";
const ESPRESSIF_OUIS = new Set([
  "24:0a:c4", "24:62:ab", "30:ae:a4", "3c:61:05", "3c:71:bf", "48:3f:da",
  "54:43:b2", "7c:df:a1", "84:0d:8e", "84:cc:a8", "84:fc:e6", "a4:cf:12",
  "ac:67:b2", "b4:e6:2d", "c4:4f:33", "c8:c9:a3", "cc:50:e3", "d8:a0:1d",
  "dc:4f:22", "e8:db:84", "ec:64:c9", "f4:cf:a2", "fc:f5:c4", "10:52:1c",
  "08:3a:f2", "08:d1:f9", "34:85:18", "2c:f4:32",
]);
const NAS_SHARES = new Set(["kingston", "slm", "backup", "home"]);
const ALLOW = process.env.MELACS_DISCOVER_ALLOW || "/etc/melacs/discover.allow";
const LOG = "/var/lib/melacs/discover.log";

function run(cmd, args, timeout) {
  return new Promise((resolve) => {
    execFile(cmd, args, { timeout }, (err, stdout) => {
      resolve(err ? "" : String(stdout || ""));
    });
  });
}

function ipToInt(text) {
  return text.split(".").reduce((acc, part) => ((acc << 8) + Number(part)) >>> 0, 0);
}

function intToIp(value) {
  return [24, 16, 8, 0].map((shift) => (value >>> shift) & 255).join(".");
}

function hostsIn(address, prefix) {
  if (prefix < 22 || prefix > 30) return [];
  const size = 2 ** (32 - prefix);
  const base = (ipToInt(address) & ((0xffffffff << (32 - prefix)) >>> 0)) >>> 0;
  const hosts = [];
  for (let i = 1; i < size - 1; i += 1) hosts.push(intToIp((base + i) >>> 0));
  return hosts;
}

async function pool(items, limit, task) {
  let cursor = 0;
  const workers = Array.from({ length: Math.min(limit, items.length) }, async () => {
    while (cursor < items.length) {
      const index = cursor;
      cursor += 1;
      await task(items[index]);
    }
  });
  await Promise.all(workers);
}

function connectOk(host, port, timeout) {
  return new Promise((resolve) => {
    const socket = net.connect({ host, port });
    const timer = setTimeout(() => {
      socket.destroy();
      resolve(false);
    }, timeout);
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

function modbusOurs(host) {
  return new Promise((resolve) => {
    const socket = net.connect({ host, port: 502 });
    const timer = setTimeout(() => {
      socket.destroy();
      resolve(false);
    }, 1200);
    const request = Buffer.from([0x00, 0x01, 0x00, 0x00, 0x00, 0x06, 0x01, 0x03, 0x00, 0x00, 0x00, 0x01]);
    socket.once("connect", () => socket.write(request));
    socket.once("data", (buf) => {
      clearTimeout(timer);
      socket.destroy();
      const unit = buf.length >= 8 && buf[2] === 0 && buf[3] === 0 && buf[6] === 1;
      resolve(unit && (buf[7] === 3 || buf[7] === 0x83));
    });
    socket.once("error", () => {
      clearTimeout(timer);
      resolve(false);
    });
  });
}

function seasPage(host) {
  return new Promise((resolve) => {
    const req = http.get({ host, port: 80, path: "/", timeout: 1200 }, (res) => {
      const chunks = [];
      res.on("data", (chunk) => {
        chunks.push(chunk);
        if (Buffer.concat(chunks).length > 8000) res.destroy();
      });
      res.on("end", () => {
        resolve(Buffer.concat(chunks).toString("utf8").includes("Melacs SEAS PLC"));
      });
    });
    req.on("timeout", () => req.destroy());
    req.on("error", () => resolve(false));
  });
}

async function nasShares(host) {
  const text = await run("smbclient", ["-g", "-N", "-L", host], 4000);
  if (!text) return [];
  return text.split("\n")
    .filter((line) => line.startsWith("Disk|") || line.startsWith("IPC|"))
    .map((line) => line.split("|")[1] || "")
    .map((name) => name.trim().toLowerCase())
    .filter((name) => NAS_SHARES.has(name));
}

function allowList() {
  try {
    return fs.readFileSync(ALLOW, "utf8").split("\n").map((line) => {
      const clean = line.replace(/#.*/, "").trim().toLowerCase();
      if (!clean) return null;
      const [key, role, ...name] = clean.split(/\s+/);
      if (role !== "pc" && role !== "nas") return null;
      return { key, role, name: name.join(" ") };
    }).filter(Boolean);
  } catch {
    return [];
  }
}

function note(line) {
  fs.mkdirSync("/var/lib/melacs", { recursive: true });
  fs.appendFileSync(LOG, `${new Date().toISOString()} ${line}\n`);
  const lines = fs.readFileSync(LOG, "utf8").trim().split("\n");
  if (lines.length > 200) fs.writeFileSync(LOG, `${lines.slice(-200).join("\n")}\n`);
}

async function localFacts() {
  const addrText = await run("ip", ["-j", "addr"], 3000);
  const addrs = JSON.parse(addrText || "[]");
  const selfAddrs = new Set();
  const selfMacs = new Set();
  const macByAddr = new Map();
  const targets = [];
  for (const iface of addrs) {
    if (!iface.addr_info || iface.ifname === "lo" || iface.ifname === "docker0") continue;
    const mac = String(iface.address || "").toLowerCase();
    if (mac) selfMacs.add(mac);
    for (const info of iface.addr_info) {
      if (info.family !== "inet") continue;
      selfAddrs.add(info.local);
      if (mac) macByAddr.set(info.local, mac);
      for (const host of hostsIn(info.local, info.prefixlen)) targets.push(host);
    }
  }
  return { selfAddrs, selfMacs, macByAddr, targets: [...new Set(targets)] };
}

async function neighbors() {
  const text = await run("ip", ["-j", "neigh"], 3000);
  const rows = JSON.parse(text || "[]");
  const seen = new Map();
  for (const row of rows) {
    const host = row.dst;
    const mac = String(row.lladdr || "").toLowerCase();
    const state = [].concat(row.state || []).join(" ");
    if (!host || !mac || host.includes(":")) continue;
    if (/FAILED|INCOMPLETE/.test(state)) continue;
    seen.set(host, mac);
  }
  return seen;
}

async function main() {
  const { selfAddrs, selfMacs, macByAddr, targets } = await localFacts();
  const selfHost = [...selfAddrs].find((addr) => !addr.startsWith("192.168.1.")) || [...selfAddrs][0] || "";
  const selfMac = macByAddr.get(selfHost) || "";
  await pool(targets, 60, (host) => run("ping", ["-c", "1", "-W", "1", host], 2000));
  const neigh = await neighbors();
  const allow = allowList();
  const found = [];
  for (const [host, mac] of neigh) {
    if (selfAddrs.has(host) || selfMacs.has(mac)) continue;
    const oui = mac.slice(0, 8);
    const allowed = allow.find((item) => item.key === mac || item.key === host);
    if (oui === MELACS7_OUI) {
      const live = await modbusOurs(host);
      found.push({
        builtinId: "melacs7",
        kind: "Melacs7",
        name: "Melacs7",
        detail: live ? "I/O-slav" : "I/O-slav, Modbus tyst",
        host,
        port: 502,
        mac,
      });
      continue;
    }
    const modbus = await modbusOurs(host);
    if (modbus && ESPRESSIF_OUIS.has(oui)) {
      found.push({
        builtinId: "challenger",
        kind: "Challenger",
        name: "Challenger",
        detail: "WiFi I/O",
        host,
        port: 502,
        mac,
      });
      continue;
    }
    if (await seasPage(host)) {
      found.push({
        kind: "Rock 5B",
        name: "SEAS",
        detail: "DietPi",
        host,
        port: 80,
        mac,
      });
      continue;
    }
    if (await connectOk(host, 445, 800)) {
      const shares = await nasShares(host);
      if (shares.length) {
        found.push({
          kind: "NAS",
          name: "NAS",
          detail: shares[0],
          host,
          port: 445,
          mac,
        });
        continue;
      }
    }
    if (allowed?.role === "pc") {
      found.push({
        kind: "PC",
        name: allowed.name || "PC",
        detail: "SEAS-dator",
        host,
        port: 22,
        mac,
      });
    } else if (allowed?.role === "nas") {
      found.push({
        kind: "NAS",
        name: allowed.name || "NAS",
        detail: "listad",
        host,
        port: 445,
        mac,
      });
    }
  }
  const changed = applyDiscovery({ selfHost, selfMac, found });
  note(`${changed ? "uppdaterade" : "oförändrat"} ${found.length} verifierade, ${neigh.size} sedda`);
  for (const item of found) note(`${item.kind} ${item.host} ${item.mac}`);
}

main().catch((err) => {
  note(`fel ${err.message || err}`);
  process.exitCode = 1;
});
