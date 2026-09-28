# Application_PLC

Ny, generell Melacs-linje. **Rör inte** `Application_OEM/` — den gamla OEM-firmwaren ligger kvar som den är.

| Del | Roll |
|---|---|
| PIC32 (`firmware_pic32`) | Alltid RTC, datalogger, I/O och Modbus-slav. Kör inte Structured Text. |
| Rock 5B (`rock5b`) | OpenPLC Runtime v4. Styrningen programmeras i webbeditorn. |
| Kontrakt (`shared`) | Samma Modbus/IEC-register för firmware, OpenPLC och dashboard. |

Utan PLC-program ligger utgångarna i safe: DIO av, AO0–AO2 är 0. Loggern skriver ändå CSV med tidsstämpel.

## Loop

1. Läs RTCC
2. Läs ingångar
3. `logger_tick()` — sampel varje sekund, medelvärde sparas var `log_period_s` (förval 6)
4. Om OpenPLC har skrivit utgångar och `safe_mode` är 0: använd den bilden
5. Annars: `safe_outputs()`
6. Skriv fysiska utgångar och publicera Modbus

Klockan ställs genom holding 202–208 tillsammans med `rtc_set` (209) = 1. Adresserna 0–201 är oförändrade.

## Bygg host-test (utan XC32)

```bash
cd Application_PLC/firmware_pic32
make host-test
```

Modbus TCP-slav mot samma karta, för OpenPLC på datorn:

```bash
./build/plc_host_test --serve
```

Port 1502, slav-id 1. Loggfil: `build/melacs_log.csv`.

## Bygg PIC32 (XC32)

Kortet är PIC32MX795F512L, 16 MHz kristall, 72 MHz systemklocka. Firmwaren är bar-metal: samma registerkarta, logger och safe-utgångar som host-testet. Den kör inte Structured Text.

```bash
cd Application_PLC/firmware_pic32
make pic32
```

Resultat: `build/melacs_pic32.hex`. Filen är inte programmerad i kretsen.

| Funktion | Hårdvara |
|---|---|
| DIO0–DIO3 | ingångar |
| DIO4–DIO7 | utgångar |
| SIP1, SIP2, SIP4–SIP7 | utgångar. SIP4 är JP7 och LED10. SIP0 och SIP3 har inget bekräftat ben |
| H1/H2 DIS, ALI, BLI | digitala utgångar |
| H1/H2 AHI, BHI | PWM, 0–65535 |
| AD0–AD7 | yttre omvandlare, råvärde |
| AI10–AI15 | inbyggd omvandlare, råvärde |
| T_BOARD | korttemperatur i grader |
| P, T1, T2 | råvärde från AD5, AD6 och AD7 |
| Klocka | yttre krets på SPI |
| Logg | `MELACS.CSV` på SD-kortet |
| Modbus TCP | port 502, slav 1, adress 192.168.1.160 |

Utan en master, eller när `safe_mode` inte är 0, är de fysiska utgångarna av. Loggern skriver ändå.
