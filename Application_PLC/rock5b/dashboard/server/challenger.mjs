import { challengerEndpoint } from "./boards.mjs";
import { createModbus } from "./modbus.mjs";

function endpoint() {
  try {
    return challengerEndpoint();
  } catch {
    return {
      host: process.env.CHALLENGER_HOST || "192.168.50.22",
      port: Number(process.env.CHALLENGER_PORT || 502),
    };
  }
}

const first = endpoint();
let host = first.host;
let port = first.port;

function blank(note) {
  return {
    id: "challenger",
    name: "Challenger RP2350",
    role: "WiFi I/O",
    host,
    link: false,
    loaded: false,
    running: false,
    error: null,
    ad: [],
    ai: [],
    dioIn: [],
    dioOut: [],
    tBoard: null,
    note,
  };
}

let current = blank("söker");
let modbus = createModbus(host, port);

function localNote(err) {
  return String(err?.message || "Challenger svarade inte").replaceAll("Melacs", "Challenger");
}

async function poll() {
  const next = endpoint();
  if (next.host !== host || next.port !== port) {
    modbus.reset();
    host = next.host;
    port = next.port;
    modbus = createModbus(host, port);
  }
  try {
    const discrete = await modbus.readBits(2, 0, 12);
    const coils = await modbus.readBits(1, 16, 4);
    const ad = await modbus.readRegs(4, 0, 4);
    const ai = await modbus.readRegs(4, 10, 4);
    const error = await modbus.readRegs(4, 20, 1);
    const temp = await modbus.readRegs(4, 30, 1);
    current = {
      id: "challenger",
      name: "Challenger RP2350",
      role: "WiFi I/O",
      host,
      link: true,
      loaded: discrete[10],
      running: discrete[11],
      error: error[0],
      ad,
      ai,
      dioIn: discrete.slice(0, 4),
      dioOut: coils,
      tBoard: temp[0],
      note: "",
    };
  } catch (err) {
    modbus.reset();
    current = blank(localNote(err));
  }
}

function delay(ms) {
  return new Promise((resolve) => {
    setTimeout(resolve, ms);
  });
}

async function loop() {
  while (true) {
    await poll();
    await delay(2000);
  }
}

loop();

export function challengerSystem() {
  return current;
}
