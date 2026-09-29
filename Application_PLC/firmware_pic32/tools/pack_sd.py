#!/usr/bin/env python3
"""Bygg C-data för README.TXT och MELACS.ZIP som kortet skriver till SD."""

import pathlib
import zipfile
import io
import sys

ROOT = pathlib.Path(__file__).resolve().parents[2]
PACK = ROOT / "sd_pack"
OUT = pathlib.Path(sys.argv[1]) if len(sys.argv) > 1 else pathlib.Path("build/sd_pack_data.c")

FILES = [
    (PACK / "README.txt", "README.txt"),
    (PACK / "project.json", "project.json"),
    (PACK / "pous/programs/main.st", "pous/programs/main.st"),
    (PACK / "devices/configuration.json", "devices/configuration.json"),
    (PACK / "devices/pin-mapping.json", "devices/pin-mapping.json"),
    (PACK / "devices/remote/Melacs.json", "devices/remote/Melacs.json"),
    (ROOT / "rock5b/openplc/modbus_master.json", "runtime/modbus_master.json"),
    (ROOT / "shared/register_map.json", "register_map.json"),
]


def c_array(name, data):
    lines = [f"const uint8_t {name}[] = {{"]
    for i in range(0, len(data), 16):
        chunk = ", ".join(str(b) for b in data[i:i + 16])
        lines.append(f"    {chunk},")
    lines.append("};")
    lines.append(f"const uint32_t {name}_len = {len(data)};")
    return "\n".join(lines)


def main():
    readme = (PACK / "README.txt").read_bytes()
    buffer = io.BytesIO()
    with zipfile.ZipFile(buffer, "w", compression=zipfile.ZIP_STORED) as archive:
        for path, arc in FILES:
            archive.write(path, arc)
    blob = buffer.getvalue()
    if not blob.startswith(b"PK"):
        raise SystemExit("zip saknar PK-header")
    OUT.parent.mkdir(parents=True, exist_ok=True)
    text = "\n".join([
        "#include <stdint.h>",
        "",
        c_array("g_sd_pack_readme", readme),
        "",
        c_array("g_sd_pack_zip", blob),
        "",
    ])
    OUT.write_text(text)
    print(f"sd pack {len(readme)} + {len(blob)} byte -> {OUT}")


if __name__ == "__main__":
    main()
