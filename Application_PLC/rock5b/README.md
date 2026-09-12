# Rock 5B — OpenPLC v4 + dashboard

Debian/Ubuntu/Armbian, arm64. Melacs (PIC32) är Modbus-slav; Rocken är klient och webbvärd.

## OpenPLC Runtime v4

```bash
git clone https://github.com/Autonomy-Logic/openplc-runtime.git
cd openplc-runtime
sudo ./install.sh
```

Editor på din Mac ansluter till `https://<rock-ip>:8443`.

Modbus mot Melacs: TCP port 502 om PIC32-Ethernet är uppe, annars RTU (`/dev/ttyUSB0`). Register: `../shared/register_map.json`.

## Dashboard

Alltid nåbar i LAN, även utan inlagt PLC-program.

```bash
cd Application_PLC/rock5b/dashboard
npm install
npm run dev -- --host
```

Produktion: `npm run build` och serva `dist/` med nginx på port 80 (`http://melacs.local`).

Utvecklingsläget använder simulerad data från registerkartan. Byt till `/api/live` när Modbus-bryggan finns.
