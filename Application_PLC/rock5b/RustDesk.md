# RustDesk

Kontorets DietPi är servern. Alla klienter använder samma adress och samma nyckel, hemma, på kontoret och på resa.

Avläst 26 oktober 2026 från kontorsnätet. Kontorets låda och datorn där är ställda enligt tabellen. Hemma-lådan svarade inte.

## Klient

| | |
|---|---|
| ID-server | `194.103.95.171:21116` |
| Relä | `194.103.95.171` |
| Nyckel | `OvhWAmGh3TvGgrQ7ZGq3+bvm0wa1HJc2gOL7jo4qov4=` |

På DietPi är klienten tjänsten `rustdesk.service`. Den startar vid boot, även när ingen är inloggad i skrivbordet. `install.sh` skriver inställningen.

## Servern

Servern är kontorets låda, `192.168.68.61`, tjänsterna `rustdesksignal` och `rustdeskrelay`. Från kontorets eget nät når man `194.103.95.171`. Deco har NAT-loopback.

TCP `21115`, `21116` och `21117` är vidarebefordrade till `192.168.68.61`.

TCP `21118`, TCP `21119`, UDP `21116` och UDP `21119` lyssnar på lådan. Deco tar inte emot UPnP, så de fyra läggs in för hand i Deco, mot `192.168.68.61`.

## Hemma

Hemma-lådan är `192.168.50.60`, ID `1743830741`, användare `root`. Från 12 november 2026 är den klient mot kontorets server, inte en egen server. `install.sh` stänger `rustdesksignal` och `rustdeskrelay`. Den gamla egna nyckeln var `vtJQ3l16vZSUbI5YWgLsvYlwKojZwr0c1lnH6UnaTls=`.

På hemmanätet är sidan `http://192.168.50.60/` och `http://melacs.local/`. På resa är det samma RustDesk-server som kontoret, och Melacs är webbläsaren på det skrivbordet. Inkommande portar behövs inte hemma.

Skrivbordet är en virtuell skärm, DUMMY0, 1920×1080. Firefox startar mot `http://127.0.0.1/`. Tangentbord i RustDesk ska stå i Legacy om Map-läget inte skriver in tecken. Klockkretsen hym8563 går inte att läsa. En omstart kan hoppa klockan. Kärnan som kan läsa HFS+ är `6.18.60`.

## Registrerade ID på kontorets server

| ID | Vad det är |
|---|---|
| `1200245339` | kontorets DietPi, `192.168.68.61` |
| `298650626` | hemma-datorns skrivbord |
| `1743830741` | `root@dietpi`, hemma-lådan, senast sedd från `94.255.242.78` |

## Ny låda

Kör `install.sh`. Lådan blir klient mot kontoret och ringer ut. På plats öppnas `http://melacs.local/`.
