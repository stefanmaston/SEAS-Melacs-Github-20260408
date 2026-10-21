# Säkerhetskrets

Kretsen faller till av när spänningen försvinner, när en ledare bryts och när 1 kHz-avbrottet slutar pulsa. Att H-bryggorna ska leda kräver att hårdslingan är sluten och att PIC32 aktivt släpper DIS. OpenPLC och en senare AI skriver bara Modbus-bilden. De har ingen ledning till reläspolen.

Den här beskrivningen är topologin. En anläggning som kan skada en person behöver dessutom ett säkerhetsrelä med känt B10d och en beräkning mot ISO 13849. PIC32-koden är skyddsfunktionerna i styrningen. Den ersätter inte reläet.

## Hårdslinga

Alla kontakter i slingan är slutna i friskt läge. Spolen på säkerhetsreläet K1 är dragen bara när hela slingan är sluten. PIC32 har inget GPIO mot den spolen.

Slingan, i serie:

1. Styrsystemets hjälpspänning.
2. Nödstopp. Kontakten öppnar när stoppet är intryckt.
3. Tryckvakt. Kontakten öppnar vid övertryck.
4. Kontakt från saknad-puls-detektorn. Den öppnar när pulsen uteblir.
5. Spolen på K1.
6. Återledning.

K1 har en normalt öppen kraftkontakt i serie med matningen till H-bryggorna JP18 och JP19. När spolen släpper försvinner kraften till bryggorna, oavsett vad DIS-benen gör. Kvittering av K1 är manuell på reläet, efter att nödstopp och tryckvakt har återgått. Kvittering via Modbus (holding 300) släpper bara PIC32:s driftförregling.

En spegelkontakt från K1 får läsas av HMI:t. Den läsningen styr inte spolen.

## Saknad puls

Timer1-avbrottet på PIC32 är 1 kHz. Varje avbrott växlar en puls-fas (`protect_kick_tick`). Detektorn på säkerhetskortet ska släppa sin kontakt om ingen flank kommit på 10 ms. Pulsledningen hör till säkerhetskortet. Den är inte ett processutgångsben på R3A, och fast program får inte använda DIO eller SIP som spolmatning.

Tills pulsledningen är dragen ska detektorns kontakt i slingan vara en bygel, och programmet ändå tvinga bryggorna av om 10 ms-svepet uteblir i mer än 100 ms. Det gör 1 kHz-avbrottet själv, via `fast_ctrl_note_time` och `fast_ctrl_sweep_kick`. En pinne som fastnat kan inte hålla K1 dragen, eftersom spolen inte går via PIC32.

## DIS

H1_DIS är RA14 och H2_DIS är RA15. Hög nivå betyder brygga av, samma som `safe_outputs`.

Dra 10 kΩ från vardera DIS-ben till 3,3 V. Vid reset är benen högimpediva, och upphämtningen håller då bryggan av. PIC32 drar benet lågt bara när den aktivt släpper på drivningen. Både reläkontakten och DIS måste vara i körläge för att bryggan ska leda.

## Skyddsfunktioner

Funktioner som märks säkerhetsrelaterade i OpenPLC-projektet kompileras till en bild som PIC32 kör. Bilden kan bara hålla utgångar i säkert läge. Den kan inte dra K1 och inte maskeras från holding 301–304. Saknas bilden, är kontrollsumman fel eller tar ett varv mer än 64 instruktioner, gäller `safe_outputs()`.
