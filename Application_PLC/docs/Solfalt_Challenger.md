# Solfält med Challenger

Plan för hur Challenger-noder sitter i ett solfält, hur de pratar med varandra och hur scada ritas från registrerade platser. Skriven 15 november 2026.

Det som kör i dag är en ensam Challenger som WiFi-Modbus-slav mot hemmalådan. Mesh, programutdelning och scada-rutnätet i det här dokumentet är inte byggt.

## Roller

ESP32-C6 på Challenger+ RP2350 har WiFi, Bluetooth LE och 802.15.4 på samma 2,4 GHz-radio. De tre ska inte köras samtidigt på varje nod.

| Nod | Radio | Uppgift |
|---|---|---|
| Hektarmaster | WiFi uppåt, 802.15.4 nedåt | En per hektar. Tar emot program och styrning från SEAS och delar ut det i fältet. |
| Strängrouter | 802.15.4 | En per sträng. Vidaresänder bara inom sin sträng. |
| Radnod | 802.15.4 | En per rad i strängen. Mäter och styr sin följare. Pratar med sin strängrouter. |
| Service | Bluetooth LE | Bredvid en följare, när någon står vid kortet. Inte bärare av fältnätet. |

Mesh-nätet i fältet går på 802.15.4. WiFi används bara av hektarmastern, upp mot den lokala SEAS. Ett löv som både mäter och kör WiFi delar samma radio.

Åttahundra noder ska inte alla vidaresända varandras trafik. 41 rader och 21 strängar ger 861 platser. Omkring 800 noder per hektar är alltså en nod per rad och sträng. Ett större fält är fler hektar.

SEAS central ska övervaka alla lokala nät. Kontorets DietPi, `192.168.68.61`, ska anpassas så att den blir den lådan. Varje lokal SEAS pratar med hektarmastrarna i sitt nät. Hemmalådan `192.168.50.60` är den lokala SEAS tills kontoret har tagit över centralen.

## Plats

Varje kort har ett serienummer och en plats. Serienumret följer kretsen. Platsen följer följaren.

| Fält | Intervall | Betydelse |
|---|---|---|
| `serial` | unikt | Kortets eget nummer. Byts när kretsen byts. |
| `hectare` | 0–1000000 | Vilket fält. |
| `string` | 0–20 | Vilken sträng i hektaren. |
| `row` | 0–40 | Vilken följare i strängen. |
| `role` | master, router, leaf | Hektarmaster, strängrouter eller radnod. |

Platsnyckeln är `hectare / string / row`. En plats har ett serienummer. Ett serienummer upptar en plats. Byts kortet behåller platsen sina nummer och får det nya serienumret.

Ett serienummer utan hektar, sträng och rad är oregistrerat. Det styr ingenting och ritas inte in i fältbilden.

## Scada

Sunthetics ska visa driften i varje enskild solfångare. Det är många noder, och det är ett krav. Ett hektarsnitt, ett medelvärde eller en ensam summa räcker inte. Varje plats ska kunna öppnas för sig: går följaren, vad mäter den, och vilket fel den har.

Bilden byggs från registret, inte från IP-adress. Hektarmastern skickar upp driften för varje serienummer. SEAS ritar den på platsen `hectare / string / row`.

- En vy per hektar.
- Kolumn är sträng 0–20.
- Rad är rad 0–40.
- En fylld cell visar länk, mätvärde och fel för den platsen.
- Tomma platser ritas tomma.
- Hektarmastern märks i sin cell.
- Oregistrerade serienummer ligger i en egen lista tills de får plats.

FUXA-sidan för en anläggning ritas inte för hand med ett kort per nod. Rutnätet kommer ur registret när noderna läses in.

## Program

Ny kod laddas sällan, och inte med USB vid varje följare.

1. SEAS lägger programbilden hos hektarmastern.
2. Mastern skickar en sträng i taget.
3. Noden behåller det gamla programmet tills det nya har startat och svarat med sin version.
4. En nod som inte svarar lämnas kvar på det gamla programmet.
5. Nästa sträng startar först när den pågående är klar eller markerad som avbruten.

Tills mesh-utdelningen finns laddas programmet med USB, som i [firmware_challenger/README.md](../firmware_challenger/README.md). Det sparade programmet ligger kvar efter strömavbrott.

## Driftgräns

Radnoden har inget eget styrprogram i den här planen. Försvinner länken till mastern stannar utgångarna. För en långsam följare är det ett godtagbart stopp. För snabb reglering eller för en säkerhetsfunktion ska skyddet sitta lokalt och trådbundet, som på Melacs7.

Modbus TCP som den ensamma labbnoden använder i dag har inget lösenord. Den som redan är inne på samma WiFi kan läsa ingångar och skriva utgångar. Fältnoderna ska inte ligga öppna på anläggningens WiFi. De når SEAS genom hektarmastern.

## Det som finns

Hemmalådans Challenger är registrerad som WiFi I/O på `192.168.50.22`, port 502, slav 1. OpenPLC på `192.168.50.60` är master. Dashboarden visar den i översiktens kedja under SEAS. Den har inget serienummer, ingen hektar, sträng eller rad, och ingen mesh.

## Nästa bygge

1. Lägg `serial`, `hectare`, `string`, `row` och `role` på ett registrerat kort.
2. Rita hektarens rutnät i översikten från de fälten.
3. Välj 802.15.4-stack på ESP32-C6 och låt hektarmastern vara den enda noden med WiFi.
4. Först därefter: programbild från mastern, en sträng i taget, med det gamla programmet kvar tills det nya svarar.
