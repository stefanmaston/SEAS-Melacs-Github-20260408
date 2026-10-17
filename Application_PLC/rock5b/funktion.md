# Melacs SEAS PLC — funktion

Melacs SEAS PLC är en egen låda med en egen webbsida. Kontona för åtkomst utifrån ligger i samma molntjänst som SEAS-webben. Användaren behöver bara en webbläsare.

## Leverans

Varje levererad anläggning är en egen installation. På det lokala nätet öppnar man lådans adress, loggar in med lösenordet som följer med leveransen och byter det vid första inloggningen. Det fungerar på dator, platta och mobil utan extra program, och det fungerar även när internet är nere.

## Programmet

Programmet ligger i en egen katalog med egna tjänster: webbsidan, kopplingen till kortet och OpenPLC. Uppdateringar av DietPi, Cockpit eller systemet rör inte den katalogen, och Melacs uppdateras som ett eget paket.

## Licens

OpenPLC startar först när licenskoden från leveransen är inskriven. Koden är signerad och kontrolleras på lådan, så den gäller även utan kontakt med molnet. Den är lådans rätt att köra anläggningen. Den är inte ett användarlösenord.

## Åtkomst utifrån

För åtkomst från andra länder används SEAS-webben, som redan har inloggning på Vercel. Ägaren bjuder in med e-post. Den inbjudna skapar sitt lösenord och ser bara de anläggningar den blivit tillagd på. Samma person kan ha tillgång till flera lådor, och varje låda kan ha flera användare.

Lådan ringer själv upp molnet. Besökarens webbläsare pratar med SEAS-sidan, och sidan når rätt låda den vägen. Ingen port öppnas i kundens router, och inget extra program installeras hos användaren.

## Behörighet

Standardlösenordet gäller bara på det lokala nätet. På avstånd loggar man in med det inbjudna kontot.

Den som bara ska se värden och den som får styra reläer är två olika behörigheter.

## Läge

På lådan finns den lokala webbsidan, inloggningen, behörigheterna för att läsa respektive styra, och licenskontrollen som måste vara gjord innan OpenPLC startar. Ett ägarkonto ligger bredvid leveranslösenordet och kan inte tas bort av de andra kontona.

Byte av lösenord vid första inloggningen, inbjudan via SEAS-webben och uppringningen till molnet är inte byggda än.
