import net from "node:net";

const upstreamHost = process.env.MELACS_UPSTREAM_HOST || "192.168.1.160";
const upstreamPort = Number(process.env.MELACS_UPSTREAM_PORT || 502);
const listenHost = process.env.MELACS_PROXY_HOST || "127.0.0.1";
const listenPort = Number(process.env.MELACS_PROXY_PORT || 1502);

let upstream = null;
let upBuffer = Buffer.alloc(0);
let connecting = null;
let waiter = null;
const queue = [];
let busy = false;

function frameSize(buffer) {
  if (buffer.length < 6) return 0;
  const length = buffer.readUInt16BE(4);
  if (length < 2 || length > 260) return -1;
  return 6 + length;
}

function failWaiter(err) {
  if (!waiter) return;
  const current = waiter;
  waiter = null;
  current.reject(err);
}

function dropUpstream() {
  const current = upstream;
  upstream = null;
  upBuffer = Buffer.alloc(0);
  failWaiter(new Error("Melacs stängde anslutningen"));
  if (current && !current.destroyed) current.destroy();
}

function onUpstreamData(chunk) {
  upBuffer = Buffer.concat([upBuffer, chunk]);
  if (!waiter) return;
  const size = frameSize(upBuffer);
  if (size < 0) {
    dropUpstream();
    return;
  }
  if (size === 0 || upBuffer.length < size) return;
  const frame = Buffer.from(upBuffer.subarray(0, size));
  upBuffer = upBuffer.subarray(size);
  const current = waiter;
  waiter = null;
  current.resolve(frame);
}

function ensureUpstream() {
  if (upstream && !upstream.destroyed && upstream.writable) return Promise.resolve();
  if (connecting) return connecting;
  connecting = new Promise((resolve, reject) => {
    const socket = net.connect({ host: upstreamHost, port: upstreamPort });
    const timer = setTimeout(() => {
      socket.destroy();
      connecting = null;
      reject(new Error("Melacs gick inte att nå"));
    }, 2000);
    socket.once("connect", () => {
      clearTimeout(timer);
      upstream = socket;
      upBuffer = Buffer.alloc(0);
      connecting = null;
      socket.on("data", onUpstreamData);
      socket.on("error", () => dropUpstream());
      socket.on("close", () => {
        if (upstream === socket) dropUpstream();
      });
      resolve();
    });
    socket.once("error", (err) => {
      clearTimeout(timer);
      connecting = null;
      reject(err);
    });
  });
  return connecting;
}

function exchange(frame) {
  return new Promise((resolve, reject) => {
    const timer = setTimeout(() => {
      waiter = null;
      dropUpstream();
      reject(new Error("Melacs svarade inte"));
    }, 1500);
    waiter = {
      resolve: (value) => {
        clearTimeout(timer);
        resolve(value);
      },
      reject: (err) => {
        clearTimeout(timer);
        reject(err);
      },
    };
    upstream.write(frame);
  });
}

async function drain() {
  if (busy) return;
  busy = true;
  try {
    while (queue.length > 0) {
      const job = queue.shift();
      if (job.socket.destroyed) continue;
      try {
        await ensureUpstream();
        const response = await exchange(job.frame);
        if (!job.socket.destroyed) job.socket.write(response);
      } catch {
        if (!job.socket.destroyed) job.socket.destroy();
      }
    }
  } finally {
    busy = false;
    if (queue.length > 0) drain();
  }
}

function pullFrames(state) {
  for (;;) {
    const size = frameSize(state.buffer);
    if (size < 0) {
      state.socket.destroy();
      return;
    }
    if (size === 0 || state.buffer.length < size) return;
    const frame = Buffer.from(state.buffer.subarray(0, size));
    state.buffer = state.buffer.subarray(size);
    queue.push({ socket: state.socket, frame });
  }
}

const server = net.createServer((socket) => {
  const state = { socket, buffer: Buffer.alloc(0) };
  socket.on("data", (chunk) => {
    state.buffer = Buffer.concat([state.buffer, chunk]);
    pullFrames(state);
    drain();
  });
  socket.on("error", () => {});
});

server.listen(listenPort, listenHost, () => {
  process.stdout.write(`modbus-proxy ${listenHost}:${listenPort} -> ${upstreamHost}:${upstreamPort}\n`);
});
