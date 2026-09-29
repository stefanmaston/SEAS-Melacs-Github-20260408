import { LOG_KEYS } from "../shared/columns.js";

function bools(values) {
  return values.map((value) => value === true || value === 1 || value === "1");
}

function u16(value, label) {
  const n = Number(value);
  if (!Number.isInteger(n) || n < 0 || n > 65535) {
    return { error: `${label} ska vara 0–65535.` };
  }
  return { value: n };
}

function daysInMonth(year, month) {
  const mdays = [0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31];
  if (month === 2 && year % 4 === 0) return 29;
  return mdays[month] || 0;
}

function clockValid(clk) {
  if (clk.year < 2000 || clk.year > 2099) return false;
  if (clk.month < 1 || clk.month > 12) return false;
  if (clk.day < 1 || clk.day > daysInMonth(clk.year, clk.month)) return false;
  if (clk.hour > 23 || clk.minute > 59 || clk.second > 59 || clk.weekday > 6) return false;
  return true;
}

function pad(n) {
  return String(n).padStart(2, "0");
}

function stamp(rtc) {
  return `${rtc.year}-${pad(rtc.month)}-${pad(rtc.day)} ${pad(rtc.hour)}:${pad(rtc.minute)}:${pad(rtc.second)}`;
}

function safeApplied(note) {
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

function rowFrom(snap) {
  const inp = snap.inputs;
  const out = snap.applied;
  return {
    TimeStamp: stamp(snap.rtc),
    AD0: inp.ad[0], AD1: inp.ad[1], AD2: inp.ad[2], AD3: inp.ad[3],
    AD4: inp.ad[4], AD5: inp.ad[5], AD6: inp.ad[6], AD7: inp.ad[7],
    DIO0: inp.dio[0] ? 1 : 0, DIO1: inp.dio[1] ? 1 : 0,
    DIO2: inp.dio[2] ? 1 : 0, DIO3: inp.dio[3] ? 1 : 0,
    AI10: inp.ai[0], AI11: inp.ai[1], AI12: inp.ai[2],
    AI13: inp.ai[3], AI14: inp.ai[4], AI15: inp.ai[5],
    sd_ok: inp.sd_ok ? 1 : 0,
    logger_ok: inp.logger_ok ? 1 : 0,
    plc_loaded: inp.plc_loaded ? 1 : 0,
    plc_running: inp.plc_running ? 1 : 0,
    error_code: inp.error_code,
    DIO4: out.dio[0] ? 1 : 0, DIO5: out.dio[1] ? 1 : 0,
    DIO6: out.dio[2] ? 1 : 0, DIO7: out.dio[3] ? 1 : 0,
    AO0: out.ao[0], AO1: out.ao[1], AO2: out.ao[2],
    SIP0: out.sip[0] ? 1 : 0, SIP1: out.sip[1] ? 1 : 0,
    SIP2: out.sip[2] ? 1 : 0, SIP3: out.sip[3] ? 1 : 0,
    SIP4: out.sip[4] ? 1 : 0, SIP5: out.sip[5] ? 1 : 0,
    SIP6: out.sip[6] ? 1 : 0, SIP7: out.sip[7] ? 1 : 0,
    H1_DIS: out.h1_dis ? 1 : 0, H1_ALI: out.h1_ali ? 1 : 0, H1_BLI: out.h1_bli ? 1 : 0,
    H1_AHI: out.h1_ahi, H1_BHI: out.h1_bhi,
    H2_DIS: out.h2_dis ? 1 : 0, H2_ALI: out.h2_ali ? 1 : 0, H2_BLI: out.h2_bli ? 1 : 0,
    H2_AHI: out.h2_ahi, H2_BHI: out.h2_bhi,
    T_BOARD: inp.t_board, P: inp.p, T1: inp.t1, T2: inp.t2, VALUE: inp.value,
    NOTE: out.note,
  };
}

export function createRemotePlant(modbus) {
  const log = [];
  let lastLogAt = 0;

  async function readSnap() {
    const discrete = await modbus.readBits(2, 0, 12);
    const inputs = await modbus.readRegs(4, 0, 35);
    const coils = await modbus.readBits(1, 16, 30);
    const analog = await modbus.readRegs(3, 100, 15);
    const holding = await modbus.readRegs(3, 200, 9);
    const commanded = {
      dio: coils.slice(0, 4),
      ao: analog.slice(0, 3),
      sip: coils.slice(16, 24),
      h1_dis: coils[24],
      h1_ali: coils[25],
      h1_bli: coils[26],
      h1_ahi: analog[10],
      h1_bhi: analog[11],
      h2_dis: coils[27],
      h2_ali: coils[28],
      h2_bli: coils[29],
      h2_ahi: analog[12],
      h2_bhi: analog[13],
      note: analog[14],
    };
    const live = {
      ad: inputs.slice(0, 8),
      dio: discrete.slice(0, 4),
      ai: inputs.slice(10, 16),
      sd_ok: discrete[8],
      logger_ok: discrete[9],
      plc_loaded: discrete[10],
      plc_running: discrete[11],
      error_code: inputs[20],
      t_board: inputs[30],
      p: inputs[31],
      t1: inputs[32],
      t2: inputs[33],
      value: inputs[34],
    };
    const rtc = {
      year: holding[2],
      month: holding[3],
      day: holding[4],
      hour: holding[5],
      minute: holding[6],
      second: holding[7],
      weekday: holding[8],
    };
    return {
      source: "modbus",
      host: "192.168.1.160",
      rtc,
      inputs: live,
      commanded,
      applied: live.plc_running ? commanded : safeApplied(commanded.note),
      holding: { safe_mode: holding[0], log_period_s: holding[1] || 6 },
      link: true,
    };
  }

  function remember(snap) {
    const period = (snap.holding.log_period_s || 6) * 1000;
    const now = Date.now();
    if (now - lastLogAt < period) return;
    lastLogAt = now;
    log.push(rowFrom(snap));
    if (log.length > 1500) log.shift();
  }

  let pending = null;
  let historyChain = Promise.resolve();

  async function readHistory(span) {
    const arm = modbus.lease();
    try {
      await modbus.writeReg(220, span);
    } catch (err) {
      if (String(err.message).includes("avvisade")) {
        throw new Error("Programmet i kortet kan inte läsa SD-loggen. Programmera om kortet.");
      }
      throw err;
    } finally {
      arm();
    }
    const deadline = Date.now() + 90000;
    let count = 0;
    let ready = false;
    while (Date.now() < deadline) {
      await new Promise((resolve) => setTimeout(resolve, 200));
      const hold = modbus.lease();
      try {
        const status = await modbus.readRegs(4, 500, 2);
        if (status[0] === 2) {
          count = status[1];
          ready = true;
          break;
        }
        if (status[0] === 3) throw new Error("SD-kortet kunde inte läsas");
      } finally {
        hold();
      }
    }
    if (!ready) throw new Error("SD-loggen hann inte läsas");
    const rows = [];
    const stride = 9;
    const page = 10;
    for (let index = 0; index < count; index += page) {
      const n = Math.min(page, count - index);
      const hold = modbus.lease();
      try {
        const regs = await modbus.readRegs(4, 510 + index * stride, n * stride);
        for (let i = 0; i < n; i += 1) {
          const base = i * stride;
          rows.push({
            TimeStamp: `${regs[base]}-${pad(regs[base + 1])}-${pad(regs[base + 2])} ${pad(regs[base + 3])}:${pad(regs[base + 4])}:${pad(regs[base + 5])}`,
            T_BOARD: regs[base + 6],
            T1: regs[base + 7],
            T2: regs[base + 8],
          });
        }
      } finally {
        hold();
      }
    }
    return { minutes: span, rows };
  }

  return {
    snapshot() {
      if (pending) return pending;
      pending = (async () => {
        const release = modbus.lease();
        try {
          let lastError = new Error("Melacs svarade inte");
          for (let attempt = 0; attempt < 3; attempt += 1) {
            try {
              const snap = await readSnap();
              remember(snap);
              return snap;
            } catch (err) {
              lastError = err;
              modbus.reset();
            }
          }
          throw lastError;
        } finally {
          release();
          pending = null;
        }
      })();
      return pending;
    },
    rows() {
      return log.slice();
    },
    async history(minutes) {
      const span = Math.max(1, Math.min(360, Number(minutes) || 10));
      const job = historyChain.then(() => readHistory(span), () => readHistory(span));
      historyChain = job.then(() => {}, () => {});
      return job;
    },
    columns: LOG_KEYS,
    async handle(body) {
      const release = modbus.lease();
      try {
      if (body.op === "clock") {
        const clk = ["year", "month", "day", "hour", "minute", "second", "weekday"].map((key) => u16(body[key], key));
        if (clk.some((item) => item.error)) return "Ogiltig tid. År 2000–2099, giltigt datum, och veckodag 0–6.";
        const fields = {
          year: clk[0].value, month: clk[1].value, day: clk[2].value,
          hour: clk[3].value, minute: clk[4].value, second: clk[5].value, weekday: clk[6].value,
        };
        if (!clockValid(fields)) return "Ogiltig tid. År 2000–2099, giltigt datum, och veckodag 0–6.";
        await modbus.writeReg(209, 0);
        await modbus.writeRegs(202, [fields.year, fields.month, fields.day, fields.hour, fields.minute, fields.second, fields.weekday, 1]);
        return null;
      }
      if (body.op === "holding") {
        if (body.safe_mode !== undefined) {
          const n = u16(body.safe_mode, "safe_mode");
          if (n.error) return n.error;
          await modbus.writeReg(200, n.value);
        }
        if (body.log_period_s !== undefined) {
          const n = u16(body.log_period_s, "Loggperiod");
          if (n.error) return n.error;
          await modbus.writeReg(201, n.value === 0 ? 6 : n.value);
        }
        return null;
      }
      if (body.op === "outputs") {
        if (Array.isArray(body.dio)) {
          if (body.dio.length !== 4) return "DIO4–DIO7 ska vara fyra värden.";
          await modbus.writeCoils(16, bools(body.dio));
        }
        if (Array.isArray(body.ao)) {
          if (body.ao.length !== 3) return "AO0–AO2 ska vara tre värden.";
          const ao = body.ao.map((value) => u16(value, "Analog utgång"));
          if (ao.some((item) => item.error)) return ao.find((item) => item.error).error;
          await modbus.writeRegs(100, ao.map((item) => item.value));
        }
        if (Array.isArray(body.sip)) {
          if (body.sip.length !== 8) return "SIP0–SIP7 ska vara åtta värden.";
          await modbus.writeCoils(32, bools(body.sip));
        }
        const coils = { h1_dis: 40, h1_ali: 41, h1_bli: 42, h2_dis: 43, h2_ali: 44, h2_bli: 45 };
        for (const [key, addr] of Object.entries(coils)) {
          if (body[key] !== undefined) await modbus.writeCoil(addr, bools([body[key]])[0]);
        }
        const levels = { h1_ahi: 110, h1_bhi: 111, h2_ahi: 112, h2_bhi: 113, note: 114 };
        for (const [key, addr] of Object.entries(levels)) {
          if (body[key] !== undefined) {
            const n = u16(body[key], key);
            if (n.error) return n.error;
            await modbus.writeReg(addr, n.value);
          }
        }
        return null;
      }
      return "Okänd åtgärd.";
      } finally {
        release();
      }
    },
  };
}
