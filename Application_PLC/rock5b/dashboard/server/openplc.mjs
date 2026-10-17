import http from "node:http";

const NAMES = ["openplc-runtime", "openplc"];

function docker(method, requestPath) {
  return new Promise((resolve, reject) => {
    const req = http.request(
      { socketPath: "/var/run/docker.sock", path: requestPath, method, timeout: 4000 },
      (res) => {
        const chunks = [];
        res.on("data", (chunk) => chunks.push(chunk));
        res.on("end", () => {
          resolve({
            status: res.statusCode || 0,
            body: Buffer.concat(chunks).toString("utf8"),
          });
        });
      },
    );
    req.on("timeout", () => {
      req.destroy();
      reject(new Error("OpenPLC svarade inte."));
    });
    req.on("error", () => reject(new Error("OpenPLC svarade inte.")));
    req.end();
  });
}

async function inspect(name) {
  const res = await docker("GET", `/containers/${name}/json`);
  if (res.status !== 200) return null;
  const info = JSON.parse(res.body);
  return {
    name,
    present: true,
    running: Boolean(info.State && info.State.Running),
    status: info.State ? info.State.Status : "",
  };
}

export async function openplcStatus() {
  try {
    for (const name of NAMES) {
      const info = await inspect(name);
      if (info) return info;
    }
    return { present: false, running: false, status: "saknas" };
  } catch (err) {
    return { present: false, running: false, status: "okänd", error: err.message };
  }
}

export async function openplcStart() {
  let found = null;
  for (const name of NAMES) {
    const info = await inspect(name);
    if (info) {
      found = info;
      break;
    }
  }
  if (!found) throw new Error("OpenPLC är inte installerad på den här lådan.");
  if (found.running) return found;
  const res = await docker("POST", `/containers/${found.name}/start`);
  if (res.status !== 204 && res.status !== 304) {
    throw new Error("OpenPLC kunde inte startas.");
  }
  return inspect(found.name);
}
