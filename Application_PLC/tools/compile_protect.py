#!/usr/bin/env python3
"""Kompilera POU:er märkta @MELACS SAFETY till en PIC32-skyddsbild.

Opkoderna är desamma som i firmware_pic32/include/protect.h.
Ett PLC-svep är 10 ms. T#100ms blir 10 svep.
"""

import argparse
import re
import socket
import struct
import sys
from pathlib import Path

OP_END = 0x00
OP_LD_BOOL = 0x01
OP_LD_WORD = 0x02
OP_LDC = 0x03
OP_NOT = 0x10
OP_AND = 0x11
OP_OR = 0x12
OP_XOR = 0x13
OP_EQ = 0x14
OP_NE = 0x15
OP_LT = 0x16
OP_GT = 0x17
OP_LE = 0x18
OP_GE = 0x19
OP_TON = 0x20
OP_RTRIG = 0x21
OP_FTRIG = 0x22
OP_INHIBIT = 0x30
OP_ST_LOCAL = 0x50
OP_LD_LOCAL = 0x51

SCAN_MS = 10
MAX_IMAGE = 256
MARK = re.compile(r"@MELACS\s+SAFETY")

INHIBIT = {
    "MELACS_INHIBIT_H1": 0x0001,
    "MELACS_INHIBIT_H2": 0x0002,
    "MELACS_INHIBIT_DIO": 0x0004,
    "MELACS_INHIBIT_SIP": 0x0008,
    "MELACS_INHIBIT_AO": 0x0010,
    "MELACS_INHIBIT_PWM": 0x0020,
    "MELACS_INHIBIT_ALL": 0x003F,
}

CMP = {
    "=": OP_EQ,
    "<>": OP_NE,
    "<": OP_LT,
    ">": OP_GT,
    "<=": OP_LE,
    ">=": OP_GE,
}


class CompileError(Exception):
    pass


def crc32(data: bytes) -> int:
    crc = 0xFFFFFFFF
    for byte in data:
        crc ^= byte
        for _ in range(8):
            crc = (crc >> 1) ^ (0xEDB88320 if crc & 1 else 0)
    return (~crc) & 0xFFFFFFFF


def wrap(body: bytes) -> bytes:
    if len(body) + 12 > MAX_IMAGE:
        raise CompileError("bilden är för lång")
    return b"MPI1" + struct.pack("<HHI", 1, len(body), crc32(body)) + body


def u16(value: int) -> bytes:
    if value < 0 or value > 0xFFFF:
        raise CompileError("värdet ryms inte i ett ord")
    return bytes((value & 0xFF, (value >> 8) & 0xFF))


def scans_of(ms: int) -> int:
    if ms < 0:
        raise CompileError("negativ tid")
    if ms == 0:
        return 0
    scans = (ms + SCAN_MS // 2) // SCAN_MS
    if scans > 0xFFFF:
        raise CompileError("tiden ryms inte")
    return scans


def strip_comments(text: str) -> str:
    text = re.sub(r"\(\*.*?\*\)", " ", text, flags=re.S)
    text = re.sub(r"//.*?$", " ", text, flags=re.M)
    return text


class Lexer:
    def __init__(self, text):
        self.tokens = []
        self.i = 0
        self._lex(text)

    def _lex(self, text):
        i = 0
        n = len(text)
        while i < n:
            if text[i].isspace():
                i += 1
                continue
            two = text[i:i + 2]
            if two in (":=", "<>", "<=", ">="):
                self.tokens.append(("sym", two))
                i += 2
                continue
            if text[i] in "():=<>;,.%":
                self.tokens.append(("sym", text[i]))
                i += 1
                continue
            match = re.match(r"(?i)(?:T|TIME)#(\d+)(MS|S|M|H)?", text[i:])
            if match:
                number = int(match.group(1))
                unit = (match.group(2) or "MS").upper()
                scale = {"MS": 1, "S": 1000, "M": 60000, "H": 3600000}[unit]
                self.tokens.append(("time", number * scale))
                i += match.end()
                continue
            match = re.match(r"\d+", text[i:])
            if match:
                self.tokens.append(("num", int(match.group())))
                i += match.end()
                continue
            match = re.match(r"[A-Za-z_][A-Za-z0-9_]*", text[i:])
            if match:
                self.tokens.append(("word", match.group().upper()))
                i += match.end()
                continue
            raise CompileError(f"okänt tecken {text[i]!r}")

    def peek(self):
        if self.i >= len(self.tokens):
            return None
        return self.tokens[self.i]

    def pop(self):
        tok = self.peek()
        if tok is None:
            raise CompileError("oväntat slut")
        self.i += 1
        return tok

    def accept_sym(self, symbol):
        tok = self.peek()
        if tok and tok[0] == "sym" and tok[1] == symbol:
            self.i += 1
            return True
        return False

    def accept_word(self, word):
        tok = self.peek()
        if tok and tok[0] == "word" and tok[1] == word:
            self.i += 1
            return True
        return False

    def expect_sym(self, symbol):
        if not self.accept_sym(symbol):
            raise CompileError(f"väntade {symbol}")

    def expect_word(self, word=None):
        tok = self.pop()
        if tok[0] != "word" or (word is not None and tok[1] != word):
            raise CompileError(f"väntade {word or 'namn'}")
        return tok[1]


class Alloc:
    def __init__(self):
        self.local = 0
        self.timer = 0
        self.edge = 0

    def take_local(self):
        if self.local >= 16:
            raise CompileError("för många lokala variabler")
        slot = self.local
        self.local += 1
        return slot

    def take_timer(self):
        if self.timer >= 8:
            raise CompileError("för många tidtagare")
        slot = self.timer
        self.timer += 1
        return slot

    def take_edge(self):
        if self.edge >= 8:
            raise CompileError("för många flanker")
        slot = self.edge
        self.edge += 1
        return slot


def parse_expr(lex):
    def parse_or():
        node = parse_and()
        while True:
            if lex.accept_word("OR"):
                node = ("or", node, parse_and())
            elif lex.accept_word("XOR"):
                node = ("xor", node, parse_and())
            else:
                break
        return node

    def parse_and():
        node = parse_cmp()
        while lex.accept_word("AND"):
            node = ("and", node, parse_cmp())
        return node

    def parse_cmp():
        node = parse_not()
        tok = lex.peek()
        if tok and tok[0] == "sym" and tok[1] in CMP:
            lex.pop()
            return ("cmp", CMP[tok[1]], node, parse_not())
        return node

    def parse_not():
        if lex.accept_word("NOT"):
            return ("not", parse_not())
        return parse_primary()

    def parse_primary():
        if lex.accept_sym("("):
            node = parse_or()
            lex.expect_sym(")")
            return node
        if lex.accept_word("TRUE"):
            return ("num", 1)
        if lex.accept_word("FALSE"):
            return ("num", 0)
        tok = lex.peek()
        if tok and tok[0] == "num":
            lex.pop()
            return ("num", tok[1])
        if tok and tok[0] == "word":
            lex.pop()
            if lex.accept_sym("."):
                field = lex.expect_word()
                return ("field", tok[1], field)
            return ("name", tok[1])
        raise CompileError("väntade uttryck")

    return parse_or()


def emit_expr(node, ctx, code):
    kind = node[0]
    if kind == "num":
        code.append(OP_LDC)
        code.extend(u16(node[1]))
        return
    if kind == "name":
        emit_name(node[1], ctx, code)
        return
    if kind == "field":
        if node[2] != "Q":
            raise CompileError(f"{node[1]}.{node[2]} kan inte läsas")
        fb = ctx["fbs"].get(node[1])
        if fb is None:
            raise CompileError(f"okänd instans {node[1]}")
        code.append(OP_LD_LOCAL)
        code.append(fb["qslot"])
        return
    if kind == "not":
        emit_expr(node[1], ctx, code)
        code.append(OP_NOT)
        return
    if kind in ("and", "or", "xor"):
        emit_expr(node[1], ctx, code)
        emit_expr(node[2], ctx, code)
        code.append({"and": OP_AND, "or": OP_OR, "xor": OP_XOR}[kind])
        return
    if kind == "cmp":
        emit_expr(node[2], ctx, code)
        emit_expr(node[3], ctx, code)
        code.append(node[1])
        return
    raise CompileError("okänt uttryck")


def emit_name(name, ctx, code):
    if name in ctx["inputs"]:
        kind, src = ctx["inputs"][name]
        code.append(OP_LD_BOOL if kind == "BOOL" else OP_LD_WORD)
        code.append(src)
        return
    if name in ctx["locals"]:
        code.append(OP_LD_LOCAL)
        code.append(ctx["locals"][name])
        return
    raise CompileError(f"okänt namn {name}")


def parse_address(lex):
    lex.expect_sym("%")
    token = lex.pop()
    if token[0] != "word":
        raise CompileError("väntade adress")
    area = token[1]
    if area.startswith("Q"):
        raise CompileError("skyddsfunktionen kan inte driva en utgång")
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
        addr = int(area[2:])
        if addr < 10 or addr > 15:
            raise CompileError("bara %IW10–%IW15 kan läsas")
        return "WORD", 4 + (addr - 10)
    raise CompileError(f"adressen {area} ingår inte i skyddsbilden")


def compile_pou(text: str, alloc: Alloc) -> bytes:
    if not MARK.search(text):
        raise CompileError("POU:n är inte märkt säkerhetsrelaterad")
    lex = Lexer(strip_comments(text))
    kind = lex.expect_word()
    if kind not in ("PROGRAM", "FUNCTION", "FUNCTION_BLOCK"):
        raise CompileError("väntade PROGRAM, FUNCTION eller FUNCTION_BLOCK")
    lex.expect_word()
    if lex.accept_sym(":"):
        lex.expect_word()
    if not lex.accept_word("VAR"):
        raise CompileError("väntade VAR")

    ctx = {"inputs": {}, "locals": {}, "fbs": {}}
    while not lex.accept_word("END_VAR"):
        name = lex.expect_word()
        if name in INHIBIT:
            raise CompileError(f"{name} är reserverat")
        if lex.accept_word("AT"):
            kind_at, src = parse_address(lex)
            lex.expect_sym(":")
            declared = lex.expect_word()
            if declared != kind_at:
                raise CompileError(f"{name} har fel typ")
            ctx["inputs"][name] = (declared, src)
        else:
            lex.expect_sym(":")
            declared = lex.expect_word()
            if declared in ("BOOL", "WORD"):
                ctx["locals"][name] = alloc.take_local()
            elif declared == "TON":
                ctx["fbs"][name] = {"op": OP_TON, "id": alloc.take_timer(), "qslot": alloc.take_local(), "timed": True}
            elif declared in ("R_TRIG", "F_TRIG"):
                op = OP_RTRIG if declared == "R_TRIG" else OP_FTRIG
                ctx["fbs"][name] = {"op": op, "id": alloc.take_edge(), "qslot": alloc.take_local(), "timed": False}
            else:
                raise CompileError(f"typen {declared} ingår inte i skyddsbilden")
        lex.expect_sym(";")

    code = bytearray()
    inhibits = 0
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
            if name in INHIBIT:
                emit_expr(expr, ctx, code)
                code.append(OP_INHIBIT)
                code.extend(u16(INHIBIT[name]))
                inhibits += 1
            elif name in ctx["locals"]:
                emit_expr(expr, ctx, code)
                code.append(OP_ST_LOCAL)
                code.append(ctx["locals"][name])
            else:
                raise CompileError(f"{name} kan inte tilldelas i en skyddsfunktion")
        lex.expect_sym(";")

    if inhibits == 0:
        raise CompileError("skyddsfunktionen tilldelar ingen spärr")
    if lex.peek() is not None:
        raise CompileError("text efter POU:n")
    return bytes(code)


def compile_project(root) -> bytes:
    root = Path(root)
    alloc = Alloc()
    chunks = []
    pous = sorted((root / "pous").rglob("*.st"))
    for path in pous:
        text = path.read_text(encoding="utf-8")
        if not MARK.search(text):
            continue
        try:
            chunks.append(compile_pou(text, alloc))
        except CompileError as exc:
            raise CompileError(f"{path.name}: {exc}") from exc
    body = b"".join(chunks) + bytes([OP_END])
    return wrap(body)


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
            raise CompileError("Modbus avvisade skyddsbilden")
        return data

    def write_one(addr, value):
        exchange(bytes((6,)) + struct.pack(">HH", addr, value))

    def write_block(addr, values):
        payload = b"".join(struct.pack(">H", v) for v in values)
        pdu = bytes((16,)) + struct.pack(">HHB", addr, len(values), len(payload)) + payload
        exchange(pdu)

    write_one(360, 1)
    write_one(361, len(image))
    offset = 0
    while offset < len(image):
        chunk = image[offset:offset + 32]
        words = []
        for i in range(0, len(chunk), 2):
            hi = chunk[i]
            lo = chunk[i + 1] if i + 1 < len(chunk) else 0
            words.append((hi << 8) | lo)
        write_block(364, [offset] + words)
        offset += len(chunk)
    write_one(360, 2)


def main(argv=None) -> int:
    parser = argparse.ArgumentParser(description="Kompilera Melacs-skyddsbild")
    parser.add_argument("project", help="OpenPLC-projekt, till exempel sd_pack")
    parser.add_argument("-o", "--output", help="fil för bilden")
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
