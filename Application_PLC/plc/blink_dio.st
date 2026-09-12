(* Minimalt program mot register_map.json — DIO0 speglas till DIO4. *)
PROGRAM blink
  VAR
    in0 AT %IX0.0 : BOOL;
    out0 AT %QX0.0 : BOOL;
  END_VAR
  out0 := in0;
END_PROGRAM

CONFIGURATION config
  RESOURCE res ON PLC
    TASK tick(INTERVAL := T#100ms, PRIORITY := 1);
    PROGRAM inst WITH tick : blink;
  END_RESOURCE
END_CONFIGURATION
