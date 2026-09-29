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

Skriptet lägger [openplc/modbus_master.json](openplc/modbus_master.json) i runtimens `conf/`. Klienten pekar på PIC32 `192.168.1.160` port 502, slav 1. Mot host-test på datorn: `127.0.0.1` port 1502 (`plc_host_test --serve`).

## Projekt på Melacs SD-kort

Källan ligger i [../sd_pack](../sd_pack). Firmwaren skriver `README.TXT` och `MELACS.ZIP` på SD-kortet om filerna saknas. Zippen är ett OpenPLC-projekt med hela Modbus-kartan, runtime-adressen och ett program som håller H-bryggornas spärr på. `MELACS.CSV` är loggen och lämnas orörd.

Packa upp zippen på datorn och öppna mappen i OpenPLC Editor 4. Välj OpenPLC Runtime v4 mot `192.168.50.60` port 8443.

Adresserna är 0-baserade och står i [../shared/register_map.json](../shared/register_map.json). Ställ klockan genom att skriva `%MW2`–`%MW8` och pulsa `%MW9` till 1 under en scan.

## Dashboard

Sidan körs på DietPi och pratar Modbus direkt med PIC32 `192.168.1.160` port 502. Öppna `http://192.168.50.60/` i nätverket. Ingen tunnel och ingen lokal Vite-process behövs.

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
