import { LOG_KEYS } from "../shared/columns.js";
import { createModbus } from "./modbus.mjs";
import { createRemotePlant } from "./remote.mjs";

function pad(n) {
  return String(n).padStart(2, "0");
}

function clamp(n, lo, hi) {
  return Math.max(lo, Math.min(hi, Math.round(n)));
}

function daysInMonth(year, month) {
  const mdays = [0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31];
  if (month === 2 && year % 4 === 0) {
    return 29;
  }
  return mdays[month] || 0;
}

function clockValid(clk) {
  if (clk.year < 2000 || clk.year > 2099) return false;
  if (clk.month < 1 || clk.month > 12) return false;
  if (clk.day < 1 || clk.day > daysInMonth(clk.year, clk.month)) return false;
  if (clk.hour > 23 || clk.minute > 59 || clk.second > 59 || clk.weekday > 6) return false;
  return true;
}

function formatTs(d) {
  return `${d.getFullYear()}-${pad(d.getMonth() + 1)}-${pad(d.getDate())} ${pad(d.getHours())}:${pad(d.getMinutes())}:${pad(d.getSeconds())}`;
}

function rtcOf(d) {
  return {
    year: d.getFullYear(),
    month: d.getMonth() + 1,
    day: d.getDate(),
    hour: d.getHours(),
    minute: d.getMinutes(),
    second: d.getSeconds(),
    weekday: d.getDay(),
  };
}

function wave(timeMs, seed, center, amp) {
  const t = timeMs / 1000;
  return center + amp * Math.sin(t / 8 + seed) + amp * 0.28 * Math.sin(t / 2.6 + seed * 1.7);
}

function safeOutputs(note) {
  return {
    dio: [false, false, false, false],
    ao: [0, 0, 0],
    sip: [false, false, false, false, false, false, false, false],
    h1_dis: true,
    h1_ali: false,
    h1_bli: false,
    h1_ahi: 0,
    h1_bhi: 0,
    h2_dis: true,
    h2_ali: false,
    h2_bli: false,
    h2_ahi: 0,
    h2_bhi: 0,
    note,
  };
}

function copyCmd(cmd) {
  return {
    dio: cmd.dio.slice(),
    ao: cmd.ao.slice(),
    sip: cmd.sip.slice(),
    h1_dis: cmd.h1_dis,
    h1_ali: cmd.h1_ali,
    h1_bli: cmd.h1_bli,
    h1_ahi: cmd.h1_ahi,
    h1_bhi: cmd.h1_bhi,
    h2_dis: cmd.h2_dis,
    h2_ali: cmd.h2_ali,
    h2_bli: cmd.h2_bli,
    h2_ahi: cmd.h2_ahi,
    h2_bhi: cmd.h2_bhi,
    note: cmd.note,
  };
}

function asBool(value) {
  return value === true || value === 1 || value === "1";
}

function asU16(value) {
  const n = Number(value);
  if (!Number.isInteger(n) || n < 0 || n > 65535) {
    return null;
  }
  return n;
}

function createPlant() {
  let offset = 0;
  let master = false;
  let safeMode = 0;
  let logPeriod = 6;
  let lastLogAt = 0;
  const log = [];
  const cmd = safeOutputs(0);
  cmd.h1_dis = true;
  cmd.h2_dis = true;

  function boardNow() {
    return new Date(Date.now() + offset);
  }

  function measure(timeMs) {
    return {
      ad: [0, 1, 2, 3, 4, 5, 6, 7].map((i) => clamp(wave(timeMs, i * 0.7, 1700 + i * 40, 280), 0, 4095)),
      dio: [Math.floor(timeMs / 4000) % 2 === 0, false, (Math.floor(timeMs / 9000) % 2) === 1, false],
      ai: [0, 1, 2, 3, 4, 5].map((i) => clamp(wave(timeMs, i + 2, 1200 + i * 30, 180), 0, 4095)),
      sd_ok: true,
      logger_ok: true,
      plc_loaded: master,
      plc_running: master && safeMode === 0,
      error_code: 0,
      t_board: clamp(wave(timeMs, 1.2, 32, 2.4), 0, 125),
      p: clamp(wave(timeMs, 2.1, 2050, 90), 0, 65535),
      t1: clamp(wave(timeMs, 0.4, 1860, 140), 0, 4095),
      t2: clamp(wave(timeMs, 2.8, 1540, 110), 0, 4095),
      value: clamp(wave(timeMs, 1.5, 620, 35), 0, 65535),
    };
  }

  function applied() {
    if (master && safeMode === 0) {
      return copyCmd(cmd);
    }
    const safe = safeOutputs(cmd.note);
    return safe;
  }

  function pushLog(timeMs) {
    const d = new Date(timeMs);
    const inp = measure(timeMs);
    const phys = applied();
    const row = {
      TimeStamp: formatTs(d),
      AD0: inp.ad[0], AD1: inp.ad[1], AD2: inp.ad[2], AD3: inp.ad[3],
      AD4: inp.ad[4], AD5: inp.ad[5], AD6: inp.ad[6], AD7: inp.ad[7],
      DIO0: inp.dio[0] ? 1 : 0,
      DIO1: inp.dio[1] ? 1 : 0,
      DIO2: inp.dio[2] ? 1 : 0,
      DIO3: inp.dio[3] ? 1 : 0,
      AI10: inp.ai[0], AI11: inp.ai[1], AI12: inp.ai[2],
      AI13: inp.ai[3], AI14: inp.ai[4], AI15: inp.ai[5],
      sd_ok: 1,
      logger_ok: 1,
      plc_loaded: master ? 1 : 0,
      plc_running: master && safeMode === 0 ? 1 : 0,
      error_code: 0,
      DIO4: phys.dio[0] ? 1 : 0,
      DIO5: phys.dio[1] ? 1 : 0,
      DIO6: phys.dio[2] ? 1 : 0,
      DIO7: phys.dio[3] ? 1 : 0,
      AO0: phys.ao[0], AO1: phys.ao[1], AO2: phys.ao[2],
      SIP0: phys.sip[0] ? 1 : 0, SIP1: phys.sip[1] ? 1 : 0,
      SIP2: phys.sip[2] ? 1 : 0, SIP3: phys.sip[3] ? 1 : 0,
      SIP4: phys.sip[4] ? 1 : 0, SIP5: phys.sip[5] ? 1 : 0,
      SIP6: phys.sip[6] ? 1 : 0, SIP7: phys.sip[7] ? 1 : 0,
      H1_DIS: phys.h1_dis ? 1 : 0,
      H1_ALI: phys.h1_ali ? 1 : 0,
      H1_BLI: phys.h1_bli ? 1 : 0,
      H1_AHI: phys.h1_ahi,
      H1_BHI: phys.h1_bhi,
      H2_DIS: phys.h2_dis ? 1 : 0,
      H2_ALI: phys.h2_ali ? 1 : 0,
      H2_BLI: phys.h2_bli ? 1 : 0,
      H2_AHI: phys.h2_ahi,
      H2_BHI: phys.h2_bhi,
      T_BOARD: inp.t_board,
      P: inp.p,
      T1: inp.t1,
      T2: inp.t2,
      VALUE: inp.value,
      NOTE: phys.note,
    };
    log.push(row);
    if (log.length > 1500) {
      log.shift();
    }
  }

  const now = Date.now();
  for (let i = 40; i >= 1; i -= 1) {
    pushLog(now - i * 6000);
  }
  lastLogAt = now;

  function maybeLog() {
    const period = (logPeriod || 6) * 1000;
    const t = Date.now();
    if (t - lastLogAt < period) {
      return;
    }
    lastLogAt = t;
    pushLog(t + offset);
  }

  function snapshot() {
    maybeLog();
    const d = boardNow();
    return {
      source: "sim",
      host: "192.168.1.160",
      rtc: rtcOf(d),
      inputs: measure(d.getTime()),
      commanded: copyCmd(cmd),
      applied: applied(),
      holding: { safe_mode: safeMode, log_period_s: logPeriod },
      link: true,
    };
  }

  function setClock(body) {
    const clk = {
      year: asU16(body.year),
      month: asU16(body.month),
      day: asU16(body.day),
      hour: asU16(body.hour),
      minute: asU16(body.minute),
      second: asU16(body.second),
      weekday: asU16(body.weekday),
    };
    if (Object.values(clk).some((v) => v === null) || !clockValid(clk)) {
      return "Ogiltig tid. År 2000–2099, giltigt datum, och veckodag 0–6.";
    }
    const target = new Date(clk.year, clk.month - 1, clk.day, clk.hour, clk.minute, clk.second);
    offset = target.getTime() - Date.now();
    return null;
  }

  function setHolding(body) {
    if (body.safe_mode !== undefined) {
      const n = asU16(body.safe_mode);
      if (n === null) return "safe_mode ska vara 0–65535.";
      safeMode = n;
    }
    if (body.log_period_s !== undefined) {
      const n = asU16(body.log_period_s);
      if (n === null) return "Loggperiod ska vara 0–65535 sekunder.";
      logPeriod = n === 0 ? 6 : n;
    }
    return null;
  }

  function setOutputs(body) {
    if (Array.isArray(body.dio)) {
      if (body.dio.length !== 4) return "DIO4–DIO7 ska vara fyra värden.";
      cmd.dio = body.dio.map(asBool);
    }
    if (Array.isArray(body.ao)) {
      if (body.ao.length !== 3) return "AO0–AO2 ska vara tre värden.";
      const ao = body.ao.map(asU16);
      if (ao.some((n) => n === null)) return "Analoga utgångar ska vara 0–65535.";
      cmd.ao = ao;
    }
    if (Array.isArray(body.sip)) {
      if (body.sip.length !== 8) return "SIP0–SIP7 ska vara åtta värden.";
      cmd.sip = body.sip.map(asBool);
    }
    const flags = ["h1_dis", "h1_ali", "h1_bli", "h2_dis", "h2_ali", "h2_bli"];
    for (const key of flags) {
      if (body[key] !== undefined) cmd[key] = asBool(body[key]);
    }
    const levels = ["h1_ahi", "h1_bhi", "h2_ahi", "h2_bhi", "note"];
    for (const key of levels) {
      if (body[key] !== undefined) {
        const n = asU16(body[key]);
        if (n === null) return `${key} ska vara 0–65535.`;
        cmd[key] = n;
      }
    }
    master = true;
    return null;
  }

  return {
    snapshot,
    rows() {
      return log.slice();
    },
    history(minutes) {
      const span = Math.max(1, Math.min(360, Number(minutes) || 10));
      const latest = log.length
        ? Date.parse(String(log[log.length - 1].TimeStamp).replace(" ", "T"))
        : Date.now();
      const start = latest - span * 60 * 1000;
      const rows = log.filter((row) => {
        const ms = Date.parse(String(row.TimeStamp).replace(" ", "T"));
        return Number.isFinite(ms) && ms >= start;
      }).map((row) => ({
        TimeStamp: row.TimeStamp,
        T_BOARD: row.T_BOARD,
        T1: row.T1,
        T2: row.T2,
      }));
      return { minutes: span, rows };
    },
    handle(body) {
      if (body.op === "clock") return setClock(body);
      if (body.op === "holding") return setHolding(body);
      if (body.op === "outputs") return setOutputs(body);
      return "Okänd åtgärd.";
    },
  };
}

const melacsHost = process.env.MELACS_HOST || "127.0.0.1";
const melacsPort = Number(process.env.MELACS_PORT || 1502);

const plant = process.env.MELACS_MODE === "sim"
  ? createPlant()
  : createRemotePlant(createModbus(melacsHost, melacsPort));

function send(res, status, payload) {
  const body = JSON.stringify(payload);
  res.statusCode = status;
  res.setHeader("Content-Type", "application/json; charset=utf-8");
  res.setHeader("Cache-Control", "no-store");
  res.end(body);
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

export function attachPlant(middlewares) {
  middlewares.use((req, res, next) => {
    const url = req.url || "";
    if (url.startsWith("/api/live") && req.method === "GET") {
      Promise.resolve(plant.snapshot()).then((snap) => {
        send(res, 200, snap);
      }).catch((err) => {
        send(res, 502, { error: err.message || "Melacs svarade inte" });
      });
      return;
    }
    if (url.startsWith("/api/history") && req.method === "GET") {
      const minutes = Number(new URL(url, "http://127.0.0.1").searchParams.get("minutes") || 10);
      Promise.resolve(plant.history(minutes)).then((payload) => {
        send(res, 200, payload);
      }).catch((err) => {
        send(res, 502, { error: err.message || "SD-loggen kunde inte läsas" });
      });
      return;
    }
    if (url.startsWith("/api/log") && req.method === "GET") {
      Promise.resolve(plant.snapshot()).then((snap) => {
        send(res, 200, { source: snap.source, columns: LOG_KEYS, rows: plant.rows() });
      }).catch((err) => {
        send(res, 502, { error: err.message || "Melacs svarade inte" });
      });
      return;
    }
    if (url.startsWith("/api/command") && req.method === "POST") {
      readBody(req).then(async (body) => {
        const error = await plant.handle(body);
        if (error) {
          send(res, 400, { error });
          return;
        }
        send(res, 200, await plant.snapshot());
      }).catch((err) => {
        send(res, 502, { error: err.message || "Melacs svarade inte" });
      });
      return;
    }
    next();
  });
}
