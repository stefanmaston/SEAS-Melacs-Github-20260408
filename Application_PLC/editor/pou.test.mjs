import assert from "node:assert/strict";
import fs from "node:fs";
import os from "node:os";
import path from "node:path";
import test from "node:test";
import {
  isLocal,
  isSafety,
  listPous,
  setLocal,
  setLocalText,
  setSafety,
  setSafetyText,
} from "./pou.mjs";

test("märket sätts och tas bort i texten", () => {
  const marked = setSafetyText("PROGRAM main\nEND_PROGRAM\n", true);
  assert.equal(isSafety(marked), true);
  assert.match(marked, /@MELACS\s+SAFETY/);
  const cleared = setSafetyText(marked, false);
  assert.equal(isSafety(cleared), false);
  assert.equal(cleared.startsWith("PROGRAM"), true);
});

test("lokal märkning tar bort skyddsmärket", () => {
  const safety = setSafetyText("PROGRAM local\nEND_PROGRAM\n", true);
  const local = setLocalText(safety, true);
  assert.equal(isLocal(local), true);
  assert.equal(isSafety(local), false);
});

test("kryssrutan skriver pragma och projektfil", () => {
  const root = fs.mkdtempSync(path.join(os.tmpdir(), "melacs-pou-"));
  const dir = path.join(root, "pous", "programs");
  fs.mkdirSync(dir, { recursive: true });
  fs.writeFileSync(path.join(dir, "main.st"), "PROGRAM main\nVAR\nEND_VAR\nEND_PROGRAM\n");
  fs.writeFileSync(path.join(root, "project.json"), JSON.stringify({ meta: { name: "t" }, data: {} }));

  let pous = setSafety(root, "pous/programs/main.st", true);
  assert.equal(pous[0].safetyRelated, true);
  assert.equal(isSafety(fs.readFileSync(path.join(dir, "main.st"), "utf8")), true);
  const project = JSON.parse(fs.readFileSync(path.join(root, "project.json"), "utf8"));
  assert.deepEqual(project.melacs.safetyRelated, ["main"]);

  pous = setLocal(root, "pous/programs/main.st", true);
  assert.equal(pous[0].localRelated, true);
  assert.equal(pous[0].safetyRelated, false);
  assert.deepEqual(
    JSON.parse(fs.readFileSync(path.join(root, "project.json"), "utf8")).melacs.localRelated,
    ["main"],
  );
  assert.deepEqual(
    JSON.parse(fs.readFileSync(path.join(root, "project.json"), "utf8")).melacs.safetyRelated,
    [],
  );

  pous = setSafety(root, "pous/programs/main.st", false);
  assert.equal(pous[0].safetyRelated, false);
  assert.equal(listPous(root)[0].name, "main");
});
