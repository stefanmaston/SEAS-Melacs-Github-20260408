(* @MELACS LOCAL *)
(* Termostat: LM35 på AD0 (%IW0), elvärme via relä SIP1 (%QX4.1).

   MCP3208 är 12 bit, 3,3 V. LM35 ger 10 mV/°C, så
     råvärde ≈ °C × 10 / 3300 × 4096
   20 °C ≈ 248,  22 °C ≈ 273.

   Hysteres utan IF: värme till under 20 °C, från över 22 °C.
   OpenPLC ska inte mappa SIP1 som utgång när den här bilden ligger i
   MELACS.LOC. H-bryggorna lämnas åt OpenPLC. *)
PROGRAM local
  VAR
    ad0 AT %IW0 : WORD;
    sip1 AT %QX4.1 : BOOL;
    heat : BOOL;
  END_VAR
  heat := (ad0 < 248) OR (heat AND (ad0 < 273));
  sip1 := heat;
END_PROGRAM
