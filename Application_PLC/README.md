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

## Bygg host-test (utan XC32)

```bash
cd Application_PLC/firmware_pic32
make host-test
./build/plc_host_test
```
