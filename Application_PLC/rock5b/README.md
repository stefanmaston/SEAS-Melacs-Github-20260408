# Rock 5B — OpenPLC v4 + dashboard

Debian/Ubuntu/Armbian, arm64. Melacs (PIC32) är Modbus-slav; Rocken är klient och webbvärd. PIC32 sköter RTC, datalogger och I/O även när inget PLC-program är inlagt.

## OpenPLC Runtime v4

```bash
git clone https://github.com/Autonomy-Logic/openplc-runtime.git
cd openplc-runtime
sudo ./install.sh
```

Runtime lyssnar på `https://192.168.50.60:8443`. Det är inget webbgränssnitt. Programmet skrivs i OpenPLC Editor på en dator.

På Rock, när runtime kör:

```bash
sudo sh openplc/prepare-runtime.sh
```

Skriptet lägger [openplc/modbus_master.json](openplc/modbus_master.json) i runtimens `conf/`. På Rock går klienten via `melacs-modbus-proxy` på `127.0.0.1` port 1502, som ensam håller sessionen mot PIC32 `192.168.1.160` port 502, slav 1. Mot host-test på datorn är samma adress `plc_host_test --serve`.

## Projekt på Melacs SD-kort

Källan ligger i [../sd_pack](../sd_pack). Firmwaren skriver `README.TXT` och `MELACS.ZIP` på SD-kortet om filerna saknas. Zippen är ett OpenPLC-projekt med hela Modbus-kartan, runtime-adressen och ett program som håller H-bryggornas spärr på. `MELACS.CSV` är loggen och lämnas orörd.

Packa upp zippen på datorn och öppna mappen i OpenPLC Editor 4. Välj OpenPLC Runtime v4 mot `192.168.50.60` port 8443.

Adresserna är 0-baserade och står i [../shared/register_map.json](../shared/register_map.json). Ställ klockan genom att skriva `%MW2`–`%MW8` och pulsa `%MW9` till 1 under en scan.

## Dashboard

Hur lådan ska användas, med lokal inloggning, licens och SEAS-webben, står i [funktion.md](funktion.md).

Sidan körs på DietPi. Öppna lådans adress i nätverket. Hemmalådan är `http://192.168.50.60/`. Kontorslådan på Deco-nätet är `http://192.168.68.61/`. Ingen tunnel och ingen lokal Vite-process behövs. Sidan och OpenPLC delar Modbus-sessionen genom `melacs-modbus-proxy` på `127.0.0.1` port 1502.

Menyn är Översikt, Scada, Reglage, Logger, Cockpit och PLC editor. PLC editor är sidan för användare, licens och anslutning av OpenPLC. Cockpit och PLC editor syns för administratör och service.

Tjänsten är `melacs-dashboard.service`. Den startar med DietPi och läser `MELACS_HOST` och `MELACS_PORT`. Filer ligger i `/opt/melacs-dashboard` (`dist/`, `server/`, `shared/columns.js`).

`melacs-net.service` lägger `192.168.1.10/24` på `eth0` vid uppstart, så Rocken når kortet på `192.168.1.160` även efter omstart. OpenPLC-containern `openplc-runtime` startar med `unless-stopped`.

Bygg och lägg upp en ny version från datorn:

```bash
cd Application_PLC/rock5b/dashboard
npm install
npm run build
```

Kopiera `dist/`, `server/` och `shared/columns.js` till `/opt/melacs-dashboard` och starta om tjänsten.

Utveckling på datorn, mot en tunnel till kortet:

```bash
MELACS_PORT=1506 npm run dev -- --host
```

`MELACS_MODE=sim` ger simulerad data. `MELACS_HOST` är `127.0.0.1` om den inte sätts.

## Scada

Processbilden är fliken Scada. Dashboarden tar emot `/fuxa` och skickar det till FUXA på `127.0.0.1` port 1881, utan prefixet `/fuxa`. FUXA själv svarar på roten. Sätt inte `BASE_PATH`. Anrop till `/api` från den fliken går till FUXA. Dashboardens egna `/api/live`, `/api/log` och `/api/command` är oförändrade.

På Rock, bara nåbar från lådan själv:

```bash
docker run -d --name melacs-fuxa --restart unless-stopped \
  -p 127.0.0.1:1881:1881 \
  frangoteam/fuxa:latest
```

`MELACS_FUXA_HOST` och `MELACS_FUXA_PORT` ändrar målet. Förval är `127.0.0.1` och `1881`.

## Datalogger, en kopia per dygn

Varje DietPi sparar dataloggen från de Melacs-kort som sitter på just den lådan. Ett kort är en rad i `/etc/melacs/datalogger-cards`. Källan är `MELACS.BAK` i kortets katalog, annars `MELACS.CSV`. Filen kopieras en gång per dygn, klockan 00:10. Samma dygn skrivs inte om.

Den lokala kopian ligger i `/var/lib/melacs/Datalogger_backup/<kort>/`. När Kingston är monterad läggs samma fil också i `/media/kingston/Datalogger_backup/<dietpi>/<kort>/`. Fler kort är fler rader, till exempel `kort-2 /var/lib/melacs/cards/kort-2`.

Skript och timer ligger i `datalogger-backup/`. På lådan heter tjänsten `melacs-datalogger-backup.timer`.
