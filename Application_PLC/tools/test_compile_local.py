#!/usr/bin/env python3
import sys
import tempfile
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))

from compile_local import CompileError, compile_pou, compile_project, crc32, Alloc
from compile_protect import compile_pou as compile_protect_pou
from compile_protect import Alloc as ProtectAlloc


class CompileLocalTest(unittest.TestCase):
    def test_local_body(self):
        image = compile_project(ROOT / "sd_pack")
        payload = image[12:]
        self.assertEqual(image[:4], b"MPL1")
        self.assertEqual(int.from_bytes(image[8:12], "little"), crc32(payload))
        self.assertEqual(int.from_bytes(payload[:4], "little"), 1 << 5)
        self.assertIn(0x40, payload[4:])

    def test_safety_mark_rejected(self):
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

    def test_unmarked_rejected(self):
        text = """PROGRAM bad
        VAR
          dio4 AT %QX0.0 : BOOL;
        END_VAR
        dio4 := TRUE;
        END_PROGRAM
        """
        with self.assertRaises(CompileError):
            compile_pou(text, Alloc())

    def test_no_output_rejected(self):
        text = """(* @MELACS LOCAL *)
        PROGRAM bad
        VAR
          flag : BOOL;
        END_VAR
        flag := TRUE;
        END_PROGRAM
        """
        with self.assertRaises(CompileError):
            compile_pou(text, Alloc())

    def test_word_output(self):
        text = """(* @MELACS LOCAL *)
        PROGRAM analog
        VAR
          ad0 AT %IW0 : WORD;
          ao0 AT %QW0 : WORD;
        END_VAR
        ao0 := ad0;
        END_PROGRAM
        """
        mask, code = compile_pou(text, Alloc())
        self.assertEqual(mask, 1 << 18)
        self.assertEqual(code, bytes((0x02, 10, 0x41, 0)))

    def test_protect_still_rejects_outputs(self):
        text = """(* @MELACS SAFETY *)
        PROGRAM bad
        VAR
          dio4 AT %QX0.0 : BOOL;
        END_VAR
        dio4 := TRUE;
        END_PROGRAM
        """
        with self.assertRaises(CompileError):
            compile_protect_pou(text, ProtectAlloc())

    def test_missing_local_pou(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            (root / "pous" / "programs").mkdir(parents=True)
            (root / "pous" / "programs" / "main.st").write_text(
                "PROGRAM main\nVAR\nEND_VAR\nEND_PROGRAM\n",
                encoding="utf-8",
            )
            with self.assertRaises(CompileError):
                compile_project(root)


if __name__ == "__main__":
    unittest.main()
