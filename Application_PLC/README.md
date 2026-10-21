# Application_PLC

Ny, generell Melacs-linje. **Rör inte** `Application_OEM/` — den gamla OEM-firmwaren ligger kvar som den är.

| Del | Roll |
|---|---|
| PIC32 (`firmware_pic32`) | Alltid RTC, datalogger, I/O och Modbus-slav. Kör inte Structured Text. |
| Rock 5B (`rock5b`) | OpenPLC Runtime v4. Styrningen programmeras i webbeditorn. |
| Kontrakt (`shared`) | Samma Modbus/IEC-register för firmware, OpenPLC och dashboard. |

Utan PLC-program ligger utgångarna i safe: DIO av, AO0–AO2 är 0. Loggern skriver ändå CSV med tidsstämpel.

## Loop

1. Läs RTCC och ingångar
2. Åldra mastern. Utebliven Modbus-trafik i 50 PLC-svep släpper den
3. Kör skyddsbilden. Saknas den, är den ogiltig eller tar varvet mer än 64 instruktioner: `safe_outputs()`
4. Om mastern är färsk, `safe_mode` är 0 och skyddsbilden är giltig: använd OpenPLC-bilden, sedan skyddsbildens spärrar
5. Annars: `safe_outputs()`
6. `logger_tick()` — sampel varje sekund, medelvärde sparas var `log_period_s` (förval 6). Raden läggs sist i filen. `MELACS.BAK` får samma rad högst en gång i timmen. Säkerhetshändelser skrivs till `MELACS.SAF` och ligger i en buffert tills Rock 5B kvitterar dem.
7. Skriv fysiska utgångar och publicera Modbus

Klockan ställs genom holding 202–208 tillsammans med `rtc_set` (209) = 1. Adresserna 0–201 är oförändrade.

## Tidbas och svarstider (PIC32)

Timer1 ger en tidbas på 1 kHz. Huvudloopen har ingen fast fördröjning:

| Takt | Vad |
|---|---|
| Varje varv | Ethernet och Modbus. En fråga besvaras normalt inom en bråkdel av en millisekund. |
| Var 10 ms | PLC-svepet ovan: I/O, logger, SD, klocka och registerbild. |
| 1 kHz, i avbrott | Snabbfunktioner: förreglingar och PID (se nedan). |

Medan SD-kortet programmerar en sektor släpps SPI-bussen och Ethernet betjänas, så loggningen stoppar inte Modbus. Tillägg till `MELACS.CSV` tar lika lång tid oavsett filens storlek; FAT-sektorn och senaste klustret cachas.

Loggfilerna öppnas bara för tillägg. En avbruten sista rad, utan radslut, tas bort när filen öppnas igen, så färdiga rader före den ligger kvar. `MELACS.BAK` är samma kolumner som dataloggen och utökas med den senaste raden högst en gång i timmen. Under den skrivningen ligger de äldre backupraderna kvar. `MELACS.SAF` är en egen fil för start, skyddsbild, master, safe mode, spärr och förregling. Samma händelser ligger i en kö på 32 poster. Rock 5B läser kön, skriver raden i sin egen `MELACS.SAF` och kvitterar holding 381. Tills kvittensen finns ligger händelsen kvar i kön, så en tillfällig nätglitch tömmer den inte.

Avbrottet rör aldrig SPI-bussen. Det använder bara DIO0–DIO3, den inbyggda ADC:n (AI10–AI15) och PWM-registren. AD0–AD7 sitter på SPI och läses i PLC-svepet.

ENC424J600:s INT-ben är inte draget till PIC32 på R3A, så Ethernet pollas.

## Snabbfunktioner, Modbus 300–339

Fyra förreglingar och två PID-kanaler körs i 1 kHz-avbrottet. Hela kartan står under `fast_ctrl` i [shared/register_map.json](shared/register_map.json) och i `firmware_pic32/include/fast_ctrl.h`.

- **Förregling** (holding 301–304): en DIO-ingång som löser ut spärrar H1, H2 eller båda inom en millisekund. Spärren är låst tills den kvitteras med holding 300 = 1 och ingången har återgått. Den gäller även i safe.
- **PID** (holding 310–319 och 320–329): återkoppling från AI10–AI15, utsignal till en av H-bryggornas PWM-kanaler. Kanalen ägs då av avbrottet och Modbus-värdet i 110–113 för den kanalen används inte. PID:en driver bara när PLC-utgångarna är släppta och bryggans DIS är låg. Samma bens lågsida (ALI/BLI) hålls av så länge PID:en äger högsidan. `out_max` är 0 från start.
- **Status** (input 300–303, 310–312, 320–322): utlösta förreglingar, tickräknare, längsta avbrottstid i µs, utsignal, återkoppling och reglerfel.

Förreglingen är en snabb driftfunktion. Nödstopp, tryckvakt och saknad-puls sitter i hårdslingan, se [docs/Sakerhetskrets.md](docs/Sakerhetskrets.md). POU:er som märks säkerhetsrelaterade i OpenPLC-projektet körs som skyddsbild i PIC32 och kan inte stängas av via holding 301–304. Märkningen görs i `editor/` och bilden byggs med `tools/compile_protect.py`.

```bash
cd Application_PLC/editor
npm install
npm test
npm run dev
```

Editorn läser POU:erna i `sd_pack/` och skriver märkningen `@MELACS SAFETY`. Bilden till PIC32 byggs sedan med `python3 tools/compile_protect.py sd_pack`. OpenPLC Editor på datorn är fortfarande verktyget för själva styrprogrammet. Displaykonceptet för två skärmar ligger i [docs/Melacs_Display_Koncept.md](docs/Melacs_Display_Koncept.md).

## Bygg host-test (utan XC32)

```bash
cd Application_PLC/firmware_pic32
make test        # unit-test för snabbfunktionerna + host-test
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
| Logg | `MELACS.CSV` på SD-kortet, bara tillägg i slutet |
| Backup | `MELACS.BAK`, samma kolumner, en ny rad högst en gång i timmen |
| Säkerhet | `MELACS.SAF` på kortet och en kopia på Rock 5B. Input 350 är äldsta händelsen, holding 381 kvitterar den |
| Hjälppaket | `README.TXT` och `MELACS.ZIP` på SD-kortet, om de saknas |
| Modbus TCP | port 502, slav 1, adress 192.168.1.160 |

Utan en färsk master, utan giltig skyddsbild, eller när `safe_mode` inte är 0, är de fysiska utgångarna av. Loggern skriver ändå.
