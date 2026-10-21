# Melacs displayenhet

Koncept, arkitektur och firmwareunderlag för dubbelskärm på Melacs7. Sammanställning 18 oktober 2026, Maston AB.

## 1. Sammanfattning

Melacs får en avtagbar displayenhet med två pekskärmar i mobilformat på den kvadratiska frontytan 140 × 140 mm. Skärmarna sitter på ett gemensamt horisontellt gångjärn mitt på frontytan. Samma enhet fungerar som vanlig PLC på vägg eller i elskåp, som experimentplattform på bord (laptopläge) och som fristående väggdisplay via kabel eller WiFi.

- **Anslutning:** Ethernet (Modbus TCP) mot en master, inte SPI direkt till Melacs-kortet.
- **Roller:** PIC32 är I/O-slav i realtid. Rock 5B är master/gateway. Displayenheten är HMI-klient och kan ta masterrollen i små installationer.
- **SoC i displayenheten:** RK3568 (två Gbit-Ethernet, två skärmar). RK3588 (Rock 5B) för stora kluster.
- **Bärkort:** ett gemensamt kort i CM4-formfaktor som kan bestyckas med billigare modul (HMI) eller RK3588-modul (master).
- **Firmware:** PIC32 har fått timerstyrd tidbas, Modbus-svar under 1 ms, SD-loggning som inte växer i tid och snabbfunktioner i 1 kHz-avbrott (gren *pic32-realtime*).

## 2. Krav

- Passar Melacs kvadratiska frontyta 140 × 140 mm.
- Två pekskärmar ungefär i mobilskärmsstorlek. Nedre skärmen kan visa tangentbord och övre data/inställningar, eller båda visar data och diagram.
- Gemensamt horisontellt gångjärn mitt på lådan i höjdled.
- Väggmonterad: nedre skärmen med tangentbordet kan fällas ut.
- Liggande på bord: tangentbordet ligger plant, övre skärmen fälls upp som på en laptop. Används som experimentplattform.
- På vägg eller i elskåp: monterad som en vanlig PLC.
- En displayenhet ska kunna användas som väggdisplay med tangentbordet anslutet via Rock 5B:s WiFi.
- Ett stort antal Melacs PLC-slavkort ska kunna styras i nätverket.
- Anslutning till Melacs-kortet via Ethernet/Modbus eller en av SPI-portarna.

## 3. Utgångsläge: Melacs7-kortet i repot

| Del | Nuläge (Application_PLC) |
|---|---|
| MCU | PIC32MX795F512L, 16 MHz kristall, 72 MHz SYSCLK, PBCLK 36 MHz |
| Ethernet | ENC424J600 på SPI3, egen TCP-stack i pic32_net.c. Modbus TCP port 502, slav 1, IP 192.168.1.160 hårdkodad |
| TCP-sessioner | En session åt gången. En andra klient får RST. Därför har Rock 5B melacs-modbus-proxy som ensam håller sessionen |
| SPI3 | Delad buss: MCP3208 (AD0–AD7), RTC, SD-kort och Ethernet. Melacs är master |
| Register | shared/register_map.json: 28 ingångar, 26 utgångar, 12 holding, logghistorik från 500 |
| Rock 5B | OpenPLC Runtime v4 (Docker), React-dashboard, modbus-proxy, melacs-net (192.168.1.10/24) |
| ENC INT-ben | Inte draget till PIC32 på R3A (går bara via R114). Avbrottsstyrt Ethernet kräver kortändring |

## 4. Gränssnitt: Ethernet, inte SPI

SPI3 är gemensam för SD, RTC, AD och Ethernet. En kabel ut till en frontpanel blir en antenn på den bussen, och ett störnings- eller kabelfel kan slå ut både loggning och nätverk samtidigt. Om SPI ändå behövs ska det vara en egen SPI-port (PIC32 har SPI1, 2 och 4) med digital isolator och en MCU som brygga. Lediga ben måste då kontrolleras i R3A-schemat.

Ethernet ger galvanisk isolation via magnetiken, lång kabel och standardverktyg. På grund av envägssessionen ska displayenheten inte vara en extra klient direkt mot ett slavkort. Den pratar med mastern, som håller den enda sessionen mot varje PIC32.

## 5. Mekanik och lägen

```
Sidovy, tre lägen (gångjärn o mitt på frontytan):
  Vägg, data på båda     Vägg, tangentbord ut     Bord, laptopläge
  |[låda]|  data              |[låda]| data                  data
  |      |  o                 |      | o                     /
  |      |  data              |      |  \ tangentbord      o___ tangentbord
                                                     [   låda   ]
```

Båda skärmarna roterar runt samma axel mitt på frontytan, åt var sitt håll. På väggen fälls den nedre ut som tangentbordshylla. På bordet ligger den nedre plant och den övre fälls upp.

### Skärmar

- 5,0 tum, 720 × 1280, IPS med kapacitiv touch (GT911 eller FT5x06 via I²C), liggande format.
- Aktiv yta ca 62 × 110 mm, ytterkontur ca 65 × 121 mm. Två paneler blir ca 130 mm plus 6–8 mm gångjärn, alltså snävt men genomförbart på 140 mm.
- En panel på 5,5–6 tum (ca 68–70 mm) ryms inte två gånger på 140 mm.
- Härdat täckglas 1,1 mm, gärna optiskt bondat, med handskläge.
- För dagsljus eller kalla teknikutrymmen: minst 800 cd/m² och –20 till +70 °C.
- Tangentbord i liggande läge: ca 11 mm per tangent med tio tangenter i bredd.

### Gångjärn

- Två oberoende friktionsgångjärn på samma axel, ett par per skärm vid axelns ändar.
- Skärm ca 60 g: egenvikt ger ca 0,02 N·m kring axeln. Tryck 3 N ytterst på utfälld tangentbordsskärm, 60 mm från axeln, ger ca 0,18 N·m. Hållmoment 0,2–0,3 N·m per skärm, delat på två gångjärn.
- Snäppläge vid 0°, 45° och 90°.
- Flexkablarna går ut vid axeln, så de utsätts mest för vridning. Två flexkablar genom gångjärnet, av typ för dynamisk böjning (valsad koppar, böjradie minst 10 × tjockleken) eller mikrokoax.

### Lägesavkänning

En magnetisk vinkelgivare per skärm (AS5600, 12 bit, I²C) och en accelerometer i lådan. Mjukvaran ser då om enheten sitter på vägg eller ligger på bord och vilka skärmar som är utfällda, och byter layout automatiskt: data på båda, tangentbord nere eller laptopläge, med rätt textrotation.

### Avtagbar enhet med PoE

Displayenheten ansluts med ett enda PoE-uttag (Ethernet och matning). Samma enhet kan då sitta på Melacs-lådan, i en skåpdörr, på väggen med lång kabel, eller gå på WiFi med separat matning.

## 6. Systemarkitektur

| Roll | Hårdvara | Uppgift |
|---|---|---|
| I/O-slav | Melacs PIC32 | Realtid, RTC, logger, säkra utgångar, snabbfunktioner. En master per kort |
| Master / gateway | Rock 5B (RK3588) eller displayenhetens SoM | melacs-modbus-proxy, OpenPLC, dashboard. Pollar alla slavkort, delar registerbilden |
| HMI-klient | Displayenheten (RK3568-modul) | Chromium i kioskläge, två fönster. Pratar alltid med mastern, aldrig direkt med slavkort |

- Samma mjukvara oavsett länk (kabel eller WiFi) och oavsett om skärmen visar tangentbord eller data. En väggdisplay kan få sitt tangentbord från en annan displayenhet, surfplatta eller mobil via Rockens WiFi.
- Rock 5B (standard) saknar inbyggd WiFi och behöver ett M.2 E-key-kort, eller byt till Rock 5B+.
- Skrivbehörighet till utgångar via WiFi ska gå genom inloggningen i auth.mjs.
- Samma image med flagga *master* eller *hmi*. Enheten kan gå från experimentplattform till del av ett större nät utan ny hårdvara.

## 7. Displayenheten som master i små installationer

Ja: OpenPLC (container), dashboard, modbus-proxy och melacs-net kan köras på displayenhetens SoM. RK3566 räcker inte för masterrollen eftersom den bara har ett Ethernet-MAC. Mastern behöver en privat länk till Melacs och en mot anläggningsnätet. RK3568 har två Gbit-Ethernet, 4 × A55, Mali-G52, ca 1 TOPS NPU, PCIe och industriella varianter (RK3568J).

| Del | RAM (ungefär) | Kommentar |
|---|---|---|
| Chromium, två helskärmsfönster | 500–900 MB | Klart tyngst |
| OpenPLC runtime v4 (Docker) | 50–100 MB | Lätt |
| Dashboard-server, proxy, Docker | 100–200 MB | Node.js |
| OS (DietPi/Debian) | ca 150 MB |  |

- 4 GB RAM ger god marginal, 2 GB är snålt. Lagring på eMMC, inte SD.
- Realtid: lås OpenPLC-containern till en egen kärna (cpuset) med högre prioritet och sätt minnestak på Chromium. PREEMPT_RT ger typiskt under ca 100 µs jitter på A55; verifiera med cyclictest.
- Testa GPU-acceleration i Chromium tidigt. Reserv: WPE WebKit (cog) i kioskläge.
- DietPis stöd följer färdiga kort. Eget bärkort behöver egen device tree. Använd leverantörens Debian-BSP, avskalad som DietPi.
- Gräns: ca 1–10 Melacs-kort med displayenheten som master. Fler kort, ML på NPU eller flera displayer mot samma kluster: Rock 5B som master.

## 8. Kostnad: RK3568 jämfört med RK3588

Skillnaden blir ungefär 40–70 USD per displayenhet. Ungefär hälften är kretsen, resten är minne, kretskort, matning och kylning.

| Krets | Styckpris små volymer |
|---|---|
| RK3568B2 (kommersiell) | ca 18–22 USD |
| RK3568J (industriell) | ca 26–29 USD |
| RK3588S | ca 52–55 USD |

| Modul (styckpris, Indien, omräknat) | Pris |
|---|---|
| Radxa CM3 (RK3566), 2 GB | ca 50 USD |
| Radxa CM3I (RK3568J), 2 GB + 8 GB eMMC | ca 64 USD exkl. moms |
| Radxa CM5 (RK3588S), 4 GB + 32 GB eMMC | ca 122 USD |

| Post | RK3568 | RK3588 |
|---|---|---|
| Kretskort (chip-down) | Typiskt 6–8 lager | Typiskt 8–10 lager, HDI, snabbare LPDDR4x/5 |
| Matning | RK809 | RK806 plus separata DC/DC, fler spänningar |
| Effekt under last | ca 3–5 W | ca 6–10 W |
| PoE | 802.3af (12,95 W) räcker | Troligen 802.3at |
| Kylning i sluten låda | Ofta passiv | Kylfläns, risk för nedklockning |

*Effektsiffrorna är typiska värden, inte uppmätta. Priserna gäller oktober 2026 och små volymer.*

### Ett gemensamt bärkort

- Enligt Radxa är CM5 (RK3588S) pin- och formfaktorkompatibel med CM3 och Raspberry Pi CM4.
- Bestyck med billig modul för HMI eller CM5 för master.
- CM4-pinouten har en Ethernet. Andra porten läggs på bärkortet via PCIe, t.ex. RTL8111H (ca 1–2 USD).
- Kontrollera i databladen att båda MIPI-DSI är utdragna på den kompatibla pinouten, och om CM3I har samma formfaktor som CM3.
- Raspberry Pi CM4/CM5 blir andra källa.
- Vid ca 10 000 enheter/år närmar man sig gränsen där egen chip-down-design lönar sig.

## 9. Prestanda jämfört med andra PLC:er

Uppdelningen RK3568 för övergripande logik och PIC32 för tidskritiska funktioner motsvarar PLCnext-konceptet. Med firmwareändringarna nedan hamnar paketet i samma klass som kompakta PLC:er med fjärr-I/O.

| Del | Före | Efter |
|---|---|---|
| Modbus-svarstid i PIC32 | 0–10 ms plus SD-toppar | under 1 ms |
| SD-loggning | Blockerande, växer med filstorlek | Konstant tid, bussen släpps under skrivning |
| Snabba funktioner i PIC32 | Inga | Timer1-avbrott 1 kHz |
| OpenPLC-cykel på RK3568 | Standardkernel | 10 ms med PREEMPT_RT på isolerad kärna |

- Kompakta PLC:er (S7-1200-klass): några ms med lokal I/O, 10–50 ms med fjärr-I/O.
- Melacs efter åtgärd: under 1 ms i PIC32, ca 10–20 ms i OpenPLC.
- Energisystem har tidskonstanter på sekunder, så 10 ms i den övergripande logiken räcker.
- Snabb rörelsestyrning och höghastighetsräkning måste ligga i PIC32.
- Säkerhetsfunktioner (nödstopp, övertryck) ska vara hårdkopplade eller certifierade.

## 10. Genomförda firmwareändringar (gren pic32-realtime)

- **Tidbas:** Timer1 1 kHz (prioritet 4). delay_ms(10) borttagen. Ethernet pollas varje varv, PLC-svepet går var 10 ms.
- **SD:** FAT-sektorcache och klustercache. Tidigare gick sd_append_line igenom hela FAT-kedjan per rad och blev långsammare ju större loggen var. Bussen släpps medan kortet programmerar en sektor och Ethernet betjänas under tiden. Ledigt-kluster-sökning börjar vid senaste träff.
- **Historik (holding 220):** startas i nästa svep på PIC32 så att en Modbus-skrivning inte avbryter en pågående SD-läsning. Status 500 visar upptagen medan begäran väntar.
- **Snabbfunktioner:** fast_ctrl.c i avbrottet. Bara DIO0–DIO3, AI10–AI15 och PWM-register, ingen SPI.
- **Portskydd:** chip select på port A och G skrivs med SET/CLR, och io_write maskar Timer1, så avbrottets spärrben inte skrivs över.
- **Bryggskydd:** när en PID äger en högsida hålls lågsidan i samma ben av, både i io_write och i avbrottet.
- **Test:** make test kör 46 enhetskontroller och host-testet. PIC32-filerna syntaxkontrollerade mot registerstub; XC32-bygge och hårdvarutest återstår.

### Modbus-block 300–339

| Adress | Typ | Innehåll |
|---|---|---|
| 300 | holding | ilk_reset: skriv 1 för att kvittera. Läses som 0 |
| 301–304 | holding | ilk_cfg: bit0–1 DIO 0–3, bit2 löser på hög, bit3 spärrar H1, bit4 spärrar H2, bit15 aktiv |
| 310–319 | holding | PID 0: enable, feedback (AI 0–5), output (PWM 0–3), setpoint, kp, ki, kd (int16 Q8.8), period_ms, out_min, out_max |
| 320–329 | holding | PID 1: samma fält |
| 300 | input | bit0–3 utlösta förreglingar, bit8 H1 spärrad, bit9 H2 spärrad |
| 301–303 | input | tickräknare, längsta avbrottstid µs, konfigurationsfel |
| 310–312, 320–322 | input | PID utsignal, återkoppling, reglerfel |

*PID kör bara när PLC-utgångarna är släppta (plc_running) och bryggans DIS är låg. out_max är 0 från start. Förreglingen är låsande, gäller även i safe, och är en driftfunktion, inte en certifierad säkerhetsfunktion.*

## 11. Många slavkort

Kapaciteten räcker: en läsning av hela registerkartan är under 200 byte. 100 kort pollade 10 gånger/s ger ca 1000 transaktioner/s och under 2 Mbit/s. Det som behöver göras:

- **IP-adress** hårdkodad i pic32_net.c. Läs från NET.CFG på SD-kortet eller holding-register i flash, alternativt DHCP-klient.
- **Identitet och upptäckt:** exponera MAC (unik från ENC424J600) och serienummer som input-register, och annonsera via UDP-broadcast.
- **Kommunikationsvakt:** utgångar till säkert läge om mastern tystnar i X sekunder. Inte genomfört än; g_master nollställs aldrig i dag.
- **Topologi:** stjärna via industriswitch fungerar direkt. Kedjekoppling kräver 3-portsswitch (t.ex. LAN9303) i MELACS7 R4. Över ca 250 kort per nät: kluster med en Rock per kluster och SEAS ovanpå.

## 12. Öppna punkter och nästa steg

- Får Rock 5B (ca 100 × 72 mm) plats i Melacs-lådan? Avgör om bordsläget blir fristående.
- Blockschema för bärkortet: SoM, två MIPI-DSI, touch, PoE-mottagare, två Ethernet, AS5600, accelerometer.
- Effektbudget som visar att 802.3af räcker i masterläge med RK3568.
- Val och prov av flexkabel eller mikrokoax genom gångjärnet.
- Kommunikationsvakt (master-timeout) i PIC32-firmwaren.
- Konfigurerbar IP och upptäckt för många slavkort.
- Hårdvarutest av pic32-realtime: make pic32, input 302 (avbrottstid), Modbus-svarstid under loggning, att SD-kortet släpper bussen under programmering.
- Kortrevision R4: dra ENC424J600 INT till PIC32 och överväg 3-portsswitch.
- Databladskontroll: DSI på CM4-pinout, CM3I formfaktor, temperaturklass.

## Källor

- LCSC, Rockchip RK3588S: https://www.lcsc.com/product-detail/C7422743.html
- Findchips, RK3568: https://www.findchips.com/search/rk3568
- Evelta, Radxa CM3I: https://evelta.com/radxa-cm3i-industrial-compute-module-embedded-som/
- ThinkRobotics, Radxa CM3I och CM5: https://thinkrobotics.com/products/radxa-cm3i, https://thinkrobotics.com/products/radxa-cm5-cm5-lite
- Allnet, Radxa CM5 (kompatibilitet): https://shop-en.allnet.de/Radxa-CM5-Rock5-RK3588S2-Compute-module-4GB-RAM-32GB-EMMC-no-Wifi/218009
- Radxa docs, CM5: https://docs.radxa.com/en/compute-module/cm5
- Repo: stefanmaston/SEAS-Melacs-Github-20260408, Application_PLC och Documents/Melacs (R3A-schema)
