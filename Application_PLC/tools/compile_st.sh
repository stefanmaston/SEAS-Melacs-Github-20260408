#!/bin/sh
# Kompilera OpenPLC/Structured Text till C som PIC32-runtimen kan länka.
# Kräver MatIEC (iec2c), samma backend som OpenPLC Editor.
set -e
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
ST="${1:-$ROOT/plc/blink_dio.st}"
OUT="$ROOT/firmware_pic32/plc_generated"

if ! command -v iec2c >/dev/null 2>&1; then
  echo "iec2c (MatIEC) saknas. Lägg ST i $ST och behåll plc_generated/config_blink.c"
  echo "eller installera MatIEC och kör: iec2c -I /usr/share/matiec \"$ST\""
  exit 0
fi

mkdir -p "$OUT"
WORKDIR="$(mktemp -d)"
cp "$ST" "$WORKDIR/program.st"
(cd "$WORKDIR" && iec2c program.st)
cp "$WORKDIR"/*.c "$WORKDIR"/*.h "$OUT/" 2>/dev/null || true
rm -rf "$WORKDIR"
echo "Genererat i $OUT — peka MPLAB på de filerna i stället för config_blink.c"
