# Rock 5B — OpenPLC v4 + dashboard

Debian/Ubuntu/Armbian, arm64. Melacs (PIC32) är Modbus-slav; Rocken är klient och webbvärd. PIC32 sköter RTC, datalogger och I/O även när inget PLC-program är inlagt.

## OpenPLC Runtime v4

```bash
git clone https://github.com/Autonomy-Logic/openplc-runtime.git
cd openplc-runtime
sudo ./install.sh
```

1. Öppna webbeditorn mot `https://<rock-ip>:8443` (desktop-editorn eller Autonomy Edge).
2. Välj OpenPLC Runtime v4 som mål och deploya dit.
3. Lägg en Modbus/TCP-klient (Remote Device) enligt [openplc/modbus_master.json](openplc/modbus_master.json). Filen kan kopieras till runtimens `core/generated/conf/modbus_master.json`.
4. På Rock pekar klienten på PIC32 `192.168.1.160` port 502. Mot host-test på datorn: `127.0.0.1` port 1502 (`plc_host_test --serve`). Saknas Ethernet används RTU `/dev/ttyUSB0` med samma register.
5. Ladda upp [../plc/blink_dio.st](../plc/blink_dio.st). `%IX0.0` är DIO0 och `%QX0.0` är DIO4.

Adresserna är 0-baserade och står i [../shared/register_map.json](../shared/register_map.json). Ställ klockan genom att skriva `%MW2`–`%MW8` och pulsa `%MW9` till 1 under en scan.

## Dashboard

Alltid nåbar i LAN, även utan inlagt PLC-program. Visar RTC, logger och senaste loggrad.

```bash
cd Application_PLC/rock5b/dashboard
npm install
npm run dev -- --host
```

Produktion: `npm run build` och serva `dist/` med nginx på port 80 (`http://melacs.local`).

Utvecklingsläget använder simulerad data från registerkartan. Byt till `/api/live` när Modbus-bryggan finns. Svaret kan innehålla `rtc` och `last_log`.
