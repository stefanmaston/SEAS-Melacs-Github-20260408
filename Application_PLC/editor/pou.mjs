import fs from "fs";
import path from "path";

const MARK_LINE = "(* @MELACS SAFETY *)";
const MARK_TEST = /@MELACS\s+SAFETY/;
const MARK_LINE_RE = /\(\*\s*@MELACS\s+SAFETY\s*\*\)\r?\n?/;

export function isSafety(text) {
  return MARK_TEST.test(text);
}

export function setSafetyText(text, safetyRelated) {
  const has = isSafety(text);
  if (safetyRelated && has) {
    return text;
  }
  if (!safetyRelated && !has) {
    return text;
  }
  if (safetyRelated) {
    return `${MARK_LINE}\n${text}`;
  }
  return text.replace(MARK_LINE_RE, "");
}

function walk(dir, out) {
  if (!fs.existsSync(dir)) {
    return;
  }
  for (const entry of fs.readdirSync(dir, { withFileTypes: true })) {
    const full = path.join(dir, entry.name);
    if (entry.isDirectory()) {
      walk(full, out);
    } else if (entry.isFile() && entry.name.endsWith(".st")) {
      out.push(full);
    }
  }
}

function pouName(text, filePath) {
  const match = text.match(/\b(PROGRAM|FUNCTION_BLOCK|FUNCTION)\s+([A-Za-z_][A-Za-z0-9_]*)/i);
  if (match) {
    return { kind: match[1].toLowerCase(), name: match[2] };
  }
  return { kind: "program", name: path.basename(filePath, ".st") };
}

export function listPous(root) {
  const files = [];
  walk(path.join(root, "pous"), files);
  files.sort();
  return files.map((full) => {
    const text = fs.readFileSync(full, "utf8");
    const info = pouName(text, full);
    return {
      path: path.relative(root, full).split(path.sep).join("/"),
      name: info.name,
      kind: info.kind,
      safetyRelated: isSafety(text),
    };
  });
}

function writeProject(root, pous) {
  const projectPath = path.join(root, "project.json");
  const project = fs.existsSync(projectPath)
    ? JSON.parse(fs.readFileSync(projectPath, "utf8"))
    : { meta: { name: "Melacs SEAS", type: "plc-project" }, data: {} };
  project.melacs = {
    safetyRelated: pous.filter((pou) => pou.safetyRelated).map((pou) => pou.name),
  };
  fs.writeFileSync(projectPath, `${JSON.stringify(project, null, 2)}\n`);
}

export function setSafety(root, relPath, safetyRelated) {
  const full = path.resolve(root, relPath);
  const pousRoot = path.resolve(root, "pous");
  if (full !== pousRoot && !full.startsWith(`${pousRoot}${path.sep}`)) {
    throw new Error("sökvägen ligger utanför projektet");
  }
  if (!full.endsWith(".st") || !fs.existsSync(full)) {
    throw new Error("POU:n finns inte");
  }
  const next = setSafetyText(fs.readFileSync(full, "utf8"), Boolean(safetyRelated));
  fs.writeFileSync(full, next);
  const pous = listPous(root);
  writeProject(root, pous);
  return pous;
}
