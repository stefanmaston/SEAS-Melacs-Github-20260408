# Application_PLC

Ny, generell Melacs-linje. **Rör inte** `Application_OEM/` — den gamla OEM-firmwaren ligger kvar som den är.

| Del | Roll |
|---|---|
| PIC32 (`firmware_pic32`) | Alltid datalogger + I/O. Kör PLC-scan om ett program är inlagt. |
| Rock 5B (`rock5b`) | OpenPLC Runtime v4 (Linux) + webbdashboard på LAN. |
| Kontrakt (`shared`) | Samma Modbus/IEC-register för firmware, OpenPLC och dashboard. |

## Loop på PIC32

1. Läs ingångar + RTCC  
2. `logger_tick()` — alltid  
3. Om PLC-program finns: `plc_scan()`  
4. Annars: `safe_outputs()`  
5. Skriv utgångar + Modbus  

## OpenPLC på PIC32

Editorn skriver Structured Text. `tools/compile_st.sh` kör MatIEC (`iec2c`) till `firmware_pic32/plc_generated/`. Runtimen anropar `config_init__` / `config_run__` varje tick (samma konvention som OpenPLC).

Program på SD (återanvänder OEM-mount `/dev/sd/d1`):

- `plc/program.st` eller `plc/program.bin` eller `plc/LOADED`

Utan fil: logger + RTC + bootloader-koll körs ändå, utgångar i safe-läge.

OEM-moduler återanvänds **utan att ändras**: `logRun.c`, `onBoardRTCC.c`, `firmwareRecoveryUpdate.c`. Se `firmware_pic32/MPLAB.md`.

## Bygg host-test (utan XC32)

```bash
cd Application_PLC/firmware_pic32
make host-test
```
