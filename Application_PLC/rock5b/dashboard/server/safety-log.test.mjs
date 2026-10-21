import fs from "node:fs";
import os from "node:os";
import path from "node:path";
import test from "node:test";
import assert from "node:assert/strict";
import { createSafetyLog } from "./safety-log.mjs";

function event(seq, code) {
  return {
    seq, code, detail: 0,
    year: 2026, month: 9, day: 27, hour: 21, minute: 0, second: seq,
  };
}

test("säkerhetsfilen växer bara i slutet och tål en omstart", () => {
  const dir = fs.mkdtempSync(path.join(os.tmpdir(), "melacs-saf-"));
  const file = path.join(dir, "MELACS.SAF");
  const log = createSafetyLog(file);
  assert.equal(fs.existsSync(file), false);
  assert.equal(log.store(event(1, 1)), 1);
  const once = fs.readFileSync(file, "utf8");
  assert.match(once, /2026-09-27 21:00:01,1,1,0/);
  assert.equal(log.store(event(1, 1)), 1);
  assert.equal(fs.readFileSync(file, "utf8"), once);
  assert.equal(log.store(event(2, 3)), 2);
  const twice = fs.readFileSync(file, "utf8");
  assert.ok(twice.startsWith(once));
  assert.match(twice, /2026-09-27 21:00:02,2,3,0/);
  const again = createSafetyLog(file);
  assert.equal(again.lastSeq(), 2);
  assert.equal(again.store(event(2, 3)), 2);
  assert.equal(fs.readFileSync(file, "utf8"), twice);
  assert.equal(again.rows().at(-1).text, "Skyddsbild saknas");
});
