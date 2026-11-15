# Challenger RP2350 som Melacs-slav

iLabs Challenger+ RP2350 WiFi6/BLE5 mäter analoga ingångar, läser digitala ingångar och styr digitala utgångar. OpenPLC är master och talar Modbus TCP mot kortet, samma adresser som i `shared/register_map.json` för de signaler kortet har.

Radiolänken är WiFi. ESP32-C6 kan BLE, men OpenPLC Runtime talar Modbus TCP och Modbus RTU, inte BLE. Därför är slaven WiFi.

Utan en färsk master, utan WiFi, eller när holding 200 inte är 0, ligger utgångarna av. En master räknas som färsk i 2 sekunder efter senaste giltiga Modbus-fråga.

## Nät

Utan sparat nät startar kortet ett eget:

| | |
|---|---|
| Namn | `Melacs-RP2350` |
| Lösen | `melacs2350` |
| Adress | `192.168.4.1` |
| Port | 502, slav-id 1 |

USB-serie (115200) skriver adressen varannan sekund. Därifrån kan nätet bytas, och valet ligger kvar efter omstart:

```text
wifi MittNat mittlosen
ap
status
```

`wifi_config.h` kan i stället fyllas i före kompilering. Namn och lösen får inte innehålla citationstecken, kommatecken eller `\`.

## Ben

Silkscreen följer Feather. Oansluten ingång läser 1 (intern pull-up). Slut till GND läser 0.

| Signal | Pin | GPIO | Betydelse |
|---|---|---|---|
| DIO0–DIO3 | D5, D6, D9, D10 | 23, 24, 25, 2 | digitala ingångar, `%IX0.0`–`%IX0.3` |
| DIO4–DIO7 | D11, D12, D13, A4 | 3, 6, 7, 1 | digitala utgångar, `%QX0.0`–`%QX0.3`. D13 är lysdioden |
| AD0–AD3 | A0–A3 | 29, 28, 27, 26 | analogt råvärde 0–4095, `%IW0`–`%IW3` |
| AI10–AI13 | samma ben | | samma kanaler i millivolt, 0–3300, `%IW10`–`%IW13` |
| AO0–AO2 | D0, D1, A5 | 13, 12, 17 | PWM 1 kHz, 0–65535, `%QW0`–`%QW2`. Kortet har ingen DAC |
| T_BOARD | — | | kärntemperatur i grader, `%IW30` |

Statusbitar som OpenPLC redan läser: `plc_loaded` (`%IX1.2`) är 1 när Modbus-servern lyssnar. `plc_running` (`%IX1.3`) är 1 när mastern är färsk och safe är av. `sd_ok` och `logger_ok` är 0. `error_code` (`%IW20`) är 0 ok, 1 WiFi nere, 2 master borta, 3 safe.

AD4–AD7, AI14–AI15, P, T1, T2, SIP och H-bryggorna finns inte på det här kortet. Registren svarar ändå, med värdet 0 eller med det senast skrivna talet, så ett bredare anrop inte felar. De driver inga ben.

OpenPLC-punkterna för det som är inkopplat ligger i `openplc_slave.json`.

## Bygg och ladda

```bash
arduino-cli compile --fqbn rp2040:rp2040:challenger_2350_wifi6_ble5 firmware_challenger/melacs_slave
arduino-cli upload -p /dev/cu.usbmodem101 --fqbn rp2040:rp2040:challenger_2350_wifi6_ble5 firmware_challenger/melacs_slave
```

Kortprofilen är **iLabs Challenger 2350 WiFi/BLE**, ESP-AT. Modbus-ramarna kan provas på datorn med `clang -std=c11 -Wall -Wextra -o /tmp/mbtest test_modbus.c melacs_slave/modbus_slave.c` från den här katalogen.
