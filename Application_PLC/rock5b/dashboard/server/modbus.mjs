import net from "node:net";

export function createModbus(host, port) {
  let socket = null;
  let buffer = Buffer.alloc(0);
  let txn = 0;
  let waiter = null;
  let chain = Promise.resolve();

  function fail(err) {
    if (!waiter) return;
    const current = waiter;
    waiter = null;
    current.reject(err);
  }

  function onData(chunk) {
    buffer = Buffer.concat([buffer, chunk]);
    while (buffer.length >= 7 && waiter) {
      const length = buffer.readUInt16BE(4);
      if (buffer.length < 6 + length) return;
      const frame = buffer.subarray(0, 6 + length);
      buffer = buffer.subarray(6 + length);
      const id = frame.readUInt16BE(0);
      const pdu = frame.subarray(7, 6 + length);
      if (id !== waiter.id) continue;
      const current = waiter;
      waiter = null;
      current.resolve(pdu);
    }
  }

  function ensure() {
    if (socket && !socket.destroyed && socket.writable) return Promise.resolve();
    return new Promise((resolve, reject) => {
      let settled = false;
      const next = net.connect({ host, port });
      const timer = setTimeout(() => {
        next.destroy();
        if (!settled) {
          settled = true;
          reject(new Error("Melacs gick inte att nå"));
        }
      }, 2000);
      next.once("connect", () => {
        clearTimeout(timer);
        socket = next;
        buffer = Buffer.alloc(0);
        if (!settled) {
          settled = true;
          resolve();
        }
      });
      next.on("data", onData);
      next.on("error", (err) => {
        clearTimeout(timer);
        if (socket === next) socket = null;
        fail(err);
        if (!settled) {
          settled = true;
          reject(err);
        }
      });
      next.on("close", () => {
        if (socket === next) socket = null;
        fail(new Error("Melacs stängde anslutningen"));
      });
    });
  }

  function request(pdu) {
    const run = async () => {
      await ensure();
      txn = (txn + 1) & 0xffff;
      const id = txn;
      const frame = Buffer.alloc(7 + pdu.length);
      frame.writeUInt16BE(id, 0);
      frame.writeUInt16BE(0, 2);
      frame.writeUInt16BE(pdu.length + 1, 4);
      frame.writeUInt8(1, 6);
      pdu.copy(frame, 7);
      return new Promise((resolve, reject) => {
        const timer = setTimeout(() => {
          if (waiter && waiter.id === id) waiter = null;
          reject(new Error("Melacs svarade inte"));
        }, 700);
        waiter = {
          id,
          resolve: (value) => {
            clearTimeout(timer);
            resolve(value);
          },
          reject: (err) => {
            clearTimeout(timer);
            reject(err);
          },
        };
        socket.write(frame);
      });
    };
    const next = chain.then(run, run);
    chain = next.then(() => {}, () => {});
    return next;
  }

  function check(pdu, fc) {
    if (pdu.length >= 2 && (pdu[0] & 0x80) !== 0) {
      throw new Error(`Melacs avvisade funktionskod ${fc}`);
    }
    if (pdu[0] !== fc) throw new Error("Oväntat svar från Melacs");
    return pdu;
  }

  async function readBits(fc, addr, count) {
    const pdu = Buffer.alloc(5);
    pdu[0] = fc;
    pdu.writeUInt16BE(addr, 1);
    pdu.writeUInt16BE(count, 3);
    const res = check(await request(pdu), fc);
    const bits = [];
    for (let i = 0; i < count; i += 1) {
      bits.push(((res[2 + (i >> 3)] >> (i & 7)) & 1) === 1);
    }
    return bits;
  }

  async function readRegs(fc, addr, count) {
    const pdu = Buffer.alloc(5);
    pdu[0] = fc;
    pdu.writeUInt16BE(addr, 1);
    pdu.writeUInt16BE(count, 3);
    const res = check(await request(pdu), fc);
    const regs = [];
    for (let i = 0; i < count; i += 1) {
      regs.push(res.readUInt16BE(2 + i * 2));
    }
    return regs;
  }

  function packBits(values) {
    const bytes = Buffer.alloc(Math.ceil(values.length / 8));
    values.forEach((on, i) => {
      if (on) bytes[i >> 3] |= 1 << (i & 7);
    });
    return bytes;
  }

  async function writeCoils(addr, values) {
    const bits = packBits(values);
    const pdu = Buffer.alloc(6 + bits.length);
    pdu[0] = 15;
    pdu.writeUInt16BE(addr, 1);
    pdu.writeUInt16BE(values.length, 3);
    pdu[5] = bits.length;
    bits.copy(pdu, 6);
    check(await request(pdu), 15);
  }

  async function writeCoil(addr, on) {
    const pdu = Buffer.alloc(5);
    pdu[0] = 5;
    pdu.writeUInt16BE(addr, 1);
    pdu.writeUInt16BE(on ? 0xff00 : 0, 3);
    check(await request(pdu), 5);
  }

  async function writeRegs(addr, values) {
    const pdu = Buffer.alloc(6 + values.length * 2);
    pdu[0] = 16;
    pdu.writeUInt16BE(addr, 1);
    pdu.writeUInt16BE(values.length, 3);
    pdu[5] = values.length * 2;
    values.forEach((value, i) => pdu.writeUInt16BE(value, 6 + i * 2));
    check(await request(pdu), 16);
  }

  async function writeReg(addr, value) {
    const pdu = Buffer.alloc(5);
    pdu[0] = 6;
    pdu.writeUInt16BE(addr, 1);
    pdu.writeUInt16BE(value, 3);
    check(await request(pdu), 6);
  }

  let depth = 0;

  function reset() {
    const current = socket;
    socket = null;
    buffer = Buffer.alloc(0);
    if (waiter) {
      const currentWaiter = waiter;
      waiter = null;
      currentWaiter.reject(new Error("Melacs svarade inte"));
    }
    if (current && !current.destroyed) current.destroy();
  }

  function close() {
    if (depth > 0) return;
    const current = socket;
    socket = null;
    buffer = Buffer.alloc(0);
    if (current && !current.destroyed) current.end();
  }

  function lease() {
    depth += 1;
    let released = false;
    return () => {
      if (released) return;
      released = true;
      depth -= 1;
      if (depth === 0) close();
    };
  }

  return { readBits, readRegs, writeCoils, writeCoil, writeRegs, writeReg, lease, reset };
}
