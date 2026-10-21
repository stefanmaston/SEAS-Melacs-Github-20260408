(* @MELACS SAFETY *)
PROGRAM guard
VAR
  dio0 AT %IX0.0 : BOOL;
  ai10 AT %IW10 : WORD;
  tmr : TON;
END_VAR
tmr(IN := dio0 AND (ai10 > 1000), PT := T#100ms);
MELACS_INHIBIT_H1 := tmr.Q;
END_PROGRAM
