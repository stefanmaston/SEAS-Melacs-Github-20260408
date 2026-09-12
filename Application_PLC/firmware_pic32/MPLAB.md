# MPLAB X — Application_PLC på PIC32MX795

Ändra inte filer i `Application_OEM`. Lägg dem som *existing items*.

## Include-sökvägar

- `Application_PLC/firmware_pic32/include`
- `Application_OEM/Top/Melacs/Application_OEM.X`

## Nya källor (den här mappen)

- `src/plc_runtime.c`
- `src/plc_iec_glue.c`
- `src/plc_scan.c`
- `src/plc_loader.c`
- `src/plat_pic32.c`
- `plc_generated/config_blink.c` (byt mot MatIEC-output när du har iec2c)

## Återanvänd från OEM (orörda)

| Modul | Filer |
|---|---|
| Datalogger | `logRun.c`, `log.h`, `oemLog.c` |
| RTC | `onBoardRTCC.c`, `onBoardRTCC.h` |
| Bootloader | `firmwareRecoveryUpdate.c`, `appheader.h`, `setup_apploader.c` |
| SD | `sd_spi.c`, `mmc.c` |
| I/O | `onBoardADC.c`, `oemInputAcquisition.c` |

Preprocessor: `APPLICATION_OEM`, `LOGGING`, `LOG_OEM` (samma som OEM `main.h`) så `LOGDATA` matchar `plat_pic32.c`.

## OpenPLC-filer på SD

Lägg program på kortet:

- `/dev/sd/d1/plc/program.st` eller `program.bin` eller flaggan `LOADED`

Runtimen kör `config_run__` varje tick om någon av dem finns. Byte av hela firmware via befintlig `bootloader_recovery_second_step()` (`FW_PATH` på SD).
