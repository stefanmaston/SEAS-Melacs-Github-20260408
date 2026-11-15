#!/usr/bin/env python3
"""Kompilera POU:er märkta @MELACS LOCAL till en PIC32-styrbild.

Opkoderna är desamma som i firmware_pic32/include/loc_runtime.h.
Ett PLC-svep är 10 ms. T#100ms blir 10 svep.
"""

import argparse
import re
import socket
import struct
import sys
from pathlib import Path

from compile_protect import (
    OP_END,
    OP_FTRIG,
    OP_LD_BOOL,
    OP_LD_LOCAL,
    OP_LD_WORD,
    OP_LDC,
    OP_RTRIG,
    OP_ST_LOCAL,
    OP_TON,
    CompileError,
    Lexer,
    crc32,
    emit_expr,
    parse_expr,
    scans_of,
    strip_comments,
    u16,
)

OP_ST_Q_BOOL = 0x40
OP_ST_Q_WORD = 0x41

MAX_IMAGE = 1024
MARK_LOCAL = re.compile(r"@MELACS\s+LOCAL")
MARK_SAFETY = re.compile(r"@MELACS\s+SAFETY")

# (own_bit, opcode channel)
Q_BOOL = {
    (0, 0): (0, 0),
    (0, 1): (1, 1),
    (0, 2): (2, 2),
    (0, 3): (3, 3),
    (4, 0): (4, 4),
    (4, 1): (5, 5),
    (4, 2): (6, 6),
    (4, 3): (7, 7),
    (4, 4): (8, 8),
    (4, 5): (9, 9),
    (4, 6): (10, 10),
    (4, 7): (11, 11),
    (5, 0): (12, 12),
    (5, 1): (13, 13),
    (5, 2): (14, 14),
    (5, 3): (15, 15),
    (5, 4): (16, 16),
    (5, 5): (17, 17),
}

Q_WORD = {
    0: (18, 0),
    1: (19, 1),
    2: (20, 2),
    10: (21, 3),
    11: (22, 4),
    12: (23, 5),
    13: (24, 6),
}


class Alloc:
    def __init__(self):
        self.local = 0
        self.timer = 0
        self.edge = 0

    def take_local(self):
        if self.local >= 32:
            raise CompileError("för många lokala variabler")
        slot = self.local
        self.local += 1
        return slot

    def take_timer(self):
        if self.timer >= 16:
            raise CompileError("för många tidtagare")
        slot = self.timer
        self.timer += 1
        return slot

    def take_edge(self):
        if self.edge >= 16:
            raise CompileError("för många flanker")
        slot = self.edge
        self.edge += 1
        return slot


def wrap(own_mask, body):
    payload = struct.pack("<I", own_mask) + body
    if len(payload) + 12 > MAX_IMAGE:
        raise CompileError("bilden är för lång")
    return b"MPL1" + struct.pack("<HHI", 1, len(payload), crc32(payload)) + payload


def parse_address(lex):
    lex.expect_sym("%")
    token = lex.pop()
    if token[0] != "word":
        raise CompileError("väntade adress")
    area = token[1]
    if area.startswith("QX"):
        byte = int(area[2:] or "0")
        lex.expect_sym(".")
        bit = lex.pop()
        if bit[0] != "num":
            raise CompileError("väntade bit")
        key = (byte, bit[1])
        if key not in Q_BOOL:
            raise CompileError(f"%QX{byte}.{bit[1]} kan inte ägas lokalt")
        own, channel = Q_BOOL[key]
        return "QBOOL", (own, channel)
    if area.startswith("QW"):
        addr = int(area[2:] or "0")
        if addr not in Q_WORD:
            raise CompileError(f"%QW{addr} kan inte ägas lokalt")
        own, channel = Q_WORD[addr]
        return "QWORD", (own, channel)
    if area.startswith("IX"):
        byte = int(area[2:] or "0")
        lex.expect_sym(".")
        bit = lex.pop()
        if bit[0] != "num":
            raise CompileError("väntade bit")
        if byte != 0 or bit[1] > 3:
            raise CompileError("bara %IX0.0–%IX0.3 kan läsas")
        return "BOOL", bit[1]
    if area.startswith("IW"):
        addr = int(area[2:] or "0")
        if 0 <= addr <= 7:
            return "WORD", 10 + addr
        if 10 <= addr <= 15:
            return "WORD", 4 + (addr - 10)
        raise CompileError("bara %IW0–%IW7 och %IW10–%IW15 kan läsas")
    raise CompileError(f"adressen {area} ingår inte i den lokala bilden")


def compile_pou(text: str, alloc: Alloc) -> tuple:
    if MARK_SAFETY.search(text):
        raise CompileError("en skydds-POU kan inte vara lokal styrning")
    if not MARK_LOCAL.search(text):
        raise CompileError("POU:n är inte märkt som lokal styrning")
    lex = Lexer(strip_comments(text))
    kind = lex.expect_word()
    if kind not in ("PROGRAM", "FUNCTION", "FUNCTION_BLOCK"):
        raise CompileError("väntade PROGRAM, FUNCTION eller FUNCTION_BLOCK")
    lex.expect_word()
    if lex.accept_sym(":"):
        lex.expect_word()
    if not lex.accept_word("VAR"):
        raise CompileError("väntade VAR")

    ctx = {"inputs": {}, "locals": {}, "fbs": {}, "outputs": {}}
    own_mask = 0
    while not lex.accept_word("END_VAR"):
        name = lex.expect_word()
        if lex.accept_word("AT"):
            declared_kind, src = parse_address(lex)
            lex.expect_sym(":")
            declared = lex.expect_word()
            if declared_kind == "QBOOL":
                if declared != "BOOL":
                    raise CompileError(f"{name} har fel typ")
                ctx["outputs"][name] = ("BOOL", src)
                own_mask |= 1 << src[0]
            elif declared_kind == "QWORD":
                if declared != "WORD":
                    raise CompileError(f"{name} har fel typ")
                ctx["outputs"][name] = ("WORD", src)
                own_mask |= 1 << src[0]
            else:
                if declared != declared_kind:
                    raise CompileError(f"{name} har fel typ")
                ctx["inputs"][name] = (declared, src)
        else:
            lex.expect_sym(":")
            declared = lex.expect_word()
            if declared in ("BOOL", "WORD"):
                ctx["locals"][name] = alloc.take_local()
            elif declared == "TON":
                ctx["fbs"][name] = {
                    "op": OP_TON,
                    "id": alloc.take_timer(),
                    "qslot": alloc.take_local(),
                    "timed": True,
                }
            elif declared in ("R_TRIG", "F_TRIG"):
                op = OP_RTRIG if declared == "R_TRIG" else OP_FTRIG
                ctx["fbs"][name] = {
                    "op": op,
                    "id": alloc.take_edge(),
                    "qslot": alloc.take_local(),
                    "timed": False,
                }
            else:
                raise CompileError(f"typen {declared} ingår inte i den lokala bilden")
        lex.expect_sym(";")

    code = bytearray()
    assigned = 0
    end = "END_" + kind
    while not lex.accept_word(end):
        name = lex.expect_word()
        if lex.accept_sym("("):
            fb = ctx["fbs"].get(name)
            if fb is None:
                raise CompileError(f"{name} är inte en tidtagare eller flank")
            args = {}
            if not lex.accept_sym(")"):
                while True:
                    key = lex.expect_word()
                    lex.expect_sym(":=")
                    if key == "PT":
                        tok = lex.pop()
                        if tok[0] != "time":
                            raise CompileError("PT ska vara en tid")
                        args["PT"] = tok[1]
                    elif key in ("IN", "CLK"):
                        args["IN"] = parse_expr(lex)
                    else:
                        raise CompileError(f"okänt argument {key}")
                    if lex.accept_sym(","):
                        continue
                    lex.expect_sym(")")
                    break
            if "IN" not in args:
                raise CompileError(f"{name} saknar IN eller CLK")
            emit_expr(args["IN"], ctx, code)
            code.append(fb["op"])
            code.append(fb["id"])
            if fb["timed"]:
                code.extend(u16(scans_of(args.get("PT", 0))))
            code.append(OP_ST_LOCAL)
            code.append(fb["qslot"])
        else:
            lex.expect_sym(":=")
            expr = parse_expr(lex)
            if name in ctx["outputs"]:
                kind_out, src = ctx["outputs"][name]
                emit_expr(expr, ctx, code)
                if kind_out == "BOOL":
                    code.append(OP_ST_Q_BOOL)
                    code.append(src[1])
                else:
                    code.append(OP_ST_Q_WORD)
                    code.append(src[1])
                assigned += 1
            elif name in ctx["locals"]:
                emit_expr(expr, ctx, code)
                code.append(OP_ST_LOCAL)
                code.append(ctx["locals"][name])
            else:
                raise CompileError(f"{name} kan inte tilldelas i lokal styrning")
        lex.expect_sym(";")

    if assigned == 0:
        raise CompileError("den lokala POU:n tilldelar ingen utgång")
    if lex.peek() is not None:
        raise CompileError("text efter POU:n")
    return own_mask, bytes(code)


def compile_project(root) -> bytes:
    root = Path(root)
    alloc = Alloc()
    own_mask = 0
    chunks = []
    pous = sorted((root / "pous").rglob("*.st"))
    for path in pous:
        text = path.read_text(encoding="utf-8")
        if not MARK_LOCAL.search(text):
            continue
        try:
            mask, code = compile_pou(text, alloc)
        except CompileError as exc:
            raise CompileError(f"{path.name}: {exc}") from exc
        own_mask |= mask
        chunks.append(code)
    if not chunks:
        raise CompileError("ingen POU är märkt som lokal styrning")
    return wrap(own_mask, b"".join(chunks) + bytes([OP_END]))


def upload(image: bytes, host: str, port: int) -> None:
    def exchange(pdu: bytes) -> bytes:
        header = b"\x00\x01\x00\x00" + struct.pack(">H", len(pdu) + 1) + b"\x01"
        with socket.create_connection((host, port), timeout=2) as sock:
            sock.sendall(header + pdu)
            mbap = sock.recv(7)
            if len(mbap) < 7:
                raise CompileError("kort Modbus-svar")
            length = struct.unpack(">H", mbap[4:6])[0] - 1
            data = b""
            while len(data) < length:
                part = sock.recv(length - len(data))
                if not part:
                    break
                data += part
        if not data or data[0] & 0x80:
            raise CompileError("Modbus avvisade den lokala bilden")
        return data

    def write_one(addr, value):
        exchange(bytes((6,)) + struct.pack(">HH", addr, value))

    def write_block(addr, values):
        payload = b"".join(struct.pack(">H", v) for v in values)
        pdu = bytes((16,)) + struct.pack(">HHB", addr, len(values), len(payload)) + payload
        exchange(pdu)

    write_one(400, 1)
    write_one(401, len(image))
    offset = 0
    while offset < len(image):
        chunk = image[offset:offset + 32]
        words = []
        for i in range(0, len(chunk), 2):
            hi = chunk[i]
            lo = chunk[i + 1] if i + 1 < len(chunk) else 0
            words.append((hi << 8) | lo)
        write_block(404, [offset] + words)
        offset += len(chunk)
    write_one(400, 2)


def main(argv=None) -> int:
    parser = argparse.ArgumentParser(description="Kompilera Melacs lokal styrbild")
    parser.add_argument("project", help="OpenPLC-projekt, till exempel sd_pack")
    parser.add_argument("-o", "--output", help="fil för bilden, till exempel MELACS.LOC")
    parser.add_argument("--upload", nargs=2, metavar=("HOST", "PORT"))
    args = parser.parse_args(argv)
    try:
        image = compile_project(args.project)
    except CompileError as exc:
        print(exc, file=sys.stderr)
        return 1
    if args.output:
        Path(args.output).write_bytes(image)
        print(f"{len(image)} byte -> {args.output}")
    else:
        print(image.hex())
    if args.upload:
        host, port = args.upload
        try:
            upload(image, host, int(port))
        except (OSError, CompileError) as exc:
            print(exc, file=sys.stderr)
            return 1
        print(f"bilden är lagd i PIC32 via {host}:{port}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
