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

Sidan körs på DietPi och startar vid strömmen. På plats öppnar man `http://melacs.local/`. Hemmalådan är också `http://192.168.50.60/`. Kontorslådan på Deco-nätet är också `http://192.168.68.61/`. Ingen tunnel och ingen lokal Vite-process behövs. Sidan och OpenPLC delar Modbus-sessionen genom `melacs-modbus-proxy` på `127.0.0.1` port 1502.

Menyn är Översikt, I/O boards, Scada, Reglage, Logger, Cockpit och PLC editor. Översikten är systemschemat. I/O boards är den tidigare översikten med systemkort, status och processbild. PLC editor är sidan för användare, licens och anslutning av OpenPLC. Cockpit och PLC editor syns för administratör och service.

## SEAS central

SEAS central ska övervaka alla lokala nät. Kontorets DietPi, `192.168.68.61`, ska anpassas så att den blir den lådan. Tills det är gjort visas rollen på hemmalådan som Lilläng SEAS, `192.168.50.60`, ovanför den lokala SEAS på samma låda. Hemmalådan förblir den lokala SEAS när kontoret har tagit över centralen.

Planen för Challenger-noder i ett solfält, med hektar, sträng, rad och mesh, står i [docs/Solfalt_Challenger.md](../docs/Solfalt_Challenger.md).

Tjänsten är `melacs-dashboard.service`. Den startar med DietPi och läser `MELACS_HOST` och `MELACS_PORT`. Filer ligger i `/opt/melacs-dashboard` (`dist/`, `server/`, `shared/columns.js`).

`melacs-net.service` lägger `192.168.1.10/24` på `eth0` vid uppstart, så Rocken når kortet på `192.168.1.160` även efter omstart. OpenPLC-containern `openplc-runtime` startar med `unless-stopped`.

Installera eller lägg upp en ny version på DietPi, som root, i den här katalogen:

```bash
./install.sh
```

Skriptet lägger dashboard, Modbus-proxy och datalogger som tjänster, stänger DietPi:s egen webbserver om den tar port 80, och släpper in TCP 80 från lokala nät om brandväggen annars spärrar. Saknas `dashboard/dist` bygger skriptet den när `npm` finns. RustDesk ställs mot kontorets server, se [RustDesk.md](RustDesk.md).

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

RustDesk-ID, adresser och nyckel för kontoret och hemma står i [RustDesk.md](RustDesk.md).

## Hemma, USB-disk

Avläst 12 november 2026 på hemma-lådan `192.168.50.60`. En Toshiba DT01ACA300 på 2,7 TB i ett Intenso USB 3.0-hölje sitter som `sda`. Systemdisken är fortfarande minneskortet.

| Volym | UUID | Montering |
|---|---|---|
| SLM | `2b14926e-0f8e-37ce-9b2d-2f103cef17e5` | `/mnt/SLM` |
| BACKUP | `77588e6b-6cc8-3e4c-8be7-9a1a5ff0bbdc` | `/mnt/BACKUP` |

Båda är journalförd HFS+ och monteras skrivskyddat. Kärnan `6.18.54` har ingen `hfsplus`-modul. `6.18.60` har den, och hemma-lådan kör den kärnan. EFI-partitionen på 300 MB delas inte ut.

Samba följer Kingston på kontoret, men bara för hemmanätet `192.168.50.0/24`. Delningarna heter SLM och BACKUP, gäst får läsa, och servern lyssnar på `127.0.0.1` och `192.168.50.60` port 445. I Finder: Gå → Anslut till server, `smb://guest@192.168.50.60`. Datorn kan också heta DietPi i nätverkslistan. Macen öppnar alla sådana diskar vid inloggning, om lådan svarar, via `~/Library/Application Support/DietPi/open-shares.sh`.

## OpenPLC på hemma efter uppdateringen 12 november 2026

Runtimen gick in i safe mode för att en kompilerad fil i containern var trasig: `venvs/modbus_slave/.../pymodbus/client/__pycache__/__init__.cpython-311.pyc` innehöll namnet `AsyncModbusSeri lClient`. Källfilen var hel. Ta bort den paketets `__pycache__` och kör `docker restart openplc-runtime`. Programmet ska då stå i RUNNING. Proxyn på `127.0.0.1:1502` håller ensam sessionen mot kortet. OpenPLC:s egna anrop direkt till `192.168.1.160:502` får connection reset så länge proxyn sitter kvar.
