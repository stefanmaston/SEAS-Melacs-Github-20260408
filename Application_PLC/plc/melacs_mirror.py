"""OpenPLC v4 Python function block.

Speglar Melacs DIO0 (discrete input 0) till DIO4 (coil 16).
I editorn: Function Block, språk Python, namn MelacsMirror.
Klistra in den här filen och anropa blocket från ett program på en task.

PIC32 är Modbus-slav id 1. Den svarar först när kortet har firmware
och går att nå på HOST nedan.
"""

import socket
import struct

HOST = "192.168.1.160"
PORT = 502
UNIT = 1
TIMEOUT_S = 1.0

_sock = None
_txn = 0
_last_on = None


def block_init():
    global _sock, _last_on
    _close()
    _last_on = None
    print("MelacsMirror start", HOST, PORT)


def block_loop():
    global _last_on
    on = _read_input()
    if on is None:
        return
    if on != _last_on:
        print("DIO0", int(on), "-> DIO4")
        _last_on = on
    _write_coil(16, on)


def _read_input():
    # FC02, discrete input 0, ett bit.
    response = _exchange(struct.pack(">BHH", 2, 0, 1))
    if response is None or len(response) < 3 or response[1] < 1:
        return None
    return bool(response[2] & 0x01)


def _write_coil(address, on):
    # FC05. 0xFF00 är ON, 0x0000 är OFF.
    value = 0xFF00 if on else 0x0000
    _exchange(struct.pack(">BHH", 5, address, value))


def _exchange(pdu):
    global _txn
    if not _connect():
        return None
    _txn = (_txn + 1) & 0xFFFF
    frame = struct.pack(">HHHB", _txn, 0, len(pdu) + 1, UNIT) + pdu
    try:
        _sock.sendall(frame)
        header = _recv(7)
        _txn_id, _protocol, length, _unit = struct.unpack(">HHHB", header)
        payload = _recv(length - 1)
    except OSError as exc:
        print("Melacs I/O", exc)
        _close()
        return None
    if not payload or payload[0] & 0x80:
        return None
    return payload


def _connect():
    global _sock
    if _sock is not None:
        return True
    try:
        sock = socket.create_connection((HOST, PORT), TIMEOUT_S)
        sock.settimeout(TIMEOUT_S)
    except OSError as exc:
        print("Melacs connect", exc)
        return False
    _sock = sock
    return True


def _recv(size):
    data = b""
    while len(data) < size:
        chunk = _sock.recv(size - len(data))
        if not chunk:
            raise OSError("connection closed")
        data += chunk
    return data


def _close():
    global _sock
    if _sock is not None:
        try:
            _sock.close()
        except OSError:
            pass
    _sock = None
