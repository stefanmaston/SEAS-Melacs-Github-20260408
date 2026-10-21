#!/usr/bin/env python3
import sys
import tempfile
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))

from compile_protect import CompileError, compile_pou, compile_project, crc32, Alloc


class CompileTest(unittest.TestCase):
    def test_guard_body(self):
        image = compile_project(ROOT / "sd_pack")
        body = image[12:]
        self.assertEqual(image[:4], b"MPI1")
        self.assertEqual(int.from_bytes(image[8:12], "little"), crc32(body))
        self.assertEqual(body, bytes((
            0x01, 0x00,
            0x02, 0x04,
            0x03, 0xE8, 0x03,
            0x17,
            0x11,
            0x20, 0x00, 0x0A, 0x00,
            0x50, 0x00,
            0x51, 0x00,
            0x30, 0x01, 0x00,
            0x00,
        )))

    def test_unmarked_project_is_empty_end(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            (root / "pous" / "programs").mkdir(parents=True)
            (root / "pous" / "programs" / "main.st").write_text(
                "PROGRAM main\nVAR\nEND_VAR\nh1_dis := TRUE;\nEND_PROGRAM\n",
                encoding="utf-8",
            )
            image = compile_project(root)
            self.assertEqual(image[12:], bytes((0x00,)))

    def test_output_assign_rejected(self):
        text = """(* @MELACS SAFETY *)
        PROGRAM bad
        VAR
          dio4 AT %QX0.0 : BOOL;
        END_VAR
        dio4 := TRUE;
        END_PROGRAM
        """
        with self.assertRaises(CompileError):
            compile_pou(text, Alloc())

    def test_plain_assign_rejected(self):
        text = """(* @MELACS SAFETY *)
        PROGRAM bad
        VAR
        END_VAR
        h1_dis := TRUE;
        END_PROGRAM
        """
        with self.assertRaises(CompileError):
            compile_pou(text, Alloc())


if __name__ == "__main__":
    unittest.main()
