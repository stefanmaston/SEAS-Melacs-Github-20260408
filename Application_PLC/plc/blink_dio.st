(* Minimalt program mot shared/register_map.json och rock5b/openplc/modbus_master.json.
   DIO0 (%IX0.0) speglas till DIO4 (%QX0.0). Ladda upp via OpenPLC-webbeditorn. *)
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
