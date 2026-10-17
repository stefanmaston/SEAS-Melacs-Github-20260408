import crypto from "node:crypto";
import fs from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";

const here = path.dirname(fileURLToPath(import.meta.url));
const plant = process.argv[2];
const keyFile = process.argv[3] || path.resolve(here, "../.license/private.pem");

if (!plant) {
  process.stderr.write("Ange anläggnings-id.\n");
  process.exit(1);
}

const key = crypto.createPrivateKey(fs.readFileSync(keyFile));
const body = Buffer.from(JSON.stringify({ v: 1, product: "melacs-seas", plant, openplc: true }));
const sig = crypto.sign(null, body, key);
process.stdout.write(`${body.toString("base64url")}.${sig.toString("base64url")}\n`);
