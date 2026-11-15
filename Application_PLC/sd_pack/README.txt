Melacs SEAS — OpenPLC-projekt

Packa upp MELACS.ZIP på datorn. Öppna mappen i OpenPLC Editor 4.
Editorn är ett program på datorn. Den finns inte som en sida i webbläsaren.

Runtime på Rock 5B
  Adress 192.168.50.60
  Port 8443, https
  Välj OpenPLC Runtime v4. Editorn frågar efter runtime-kontot.

Melacs är Modbus-slav
  192.168.1.160 port 502, slav 1
  Kartan i editorn är devices/remote/Melacs.json
  Samma karta för runtime ligger i runtime/modbus_master.json
  Registernamnen står i register_map.json

Programmet main håller H1_DIS och H2_DIS på TRUE.
TRUE betyder att H-bryggorna JP18 och JP19 är av.
Släpp spärren bara när drivningen ska vara på.

Kortet lämnar de fysiska utgångarna av tills en master har skrivit
inom de senaste 50 PLC-svepen, safe_mode (%MW0) är 0 och en giltig
skyddsbild ligger i PIC32. 1 i safe_mode betyder säkra utgångar.

Säkerhetsrelaterad POU
  Kryssa i Melacs skyddsmärkning (Application_PLC/editor).
  Märket är kommentaren (* @MELACS SAFETY *) överst i POU-filen
  och namnet i project.json under melacs.safetyRelated.
  guard är märkt. main är vanlig styrning mot OpenPLC Runtime.
  Bygg bilden med tools/compile_protect.py och lägg den i PIC32
  via --upload. Bilden kan bara spärra utgångar.
  Nödstopp och tryckvakt är hårdkopplade, se docs/Sakerhetskrets.md.

Lokal styr-POU
  Märket är (* @MELACS LOCAL *). local är en LM35-termostat på AD0
  som slår SIP1 (elvärme) under 20 °C och släpper över 22 °C.
  Bygg med python3 tools/compile_local.py sd_pack -o MELACS.LOC
  och lägg MELACS.LOC på det här kortet. PIC32 kör den vid start,
  även utan OpenPLC Runtime. OpenPLC får inte skriva de utgångar
  den lokala POU:n äger; övriga utgångar är oförändrade.

MELACS.LOC är den lokala styrbilden. Saknas filen körs ingen lokal POU.
MELACS.CSV på det här kortet är dataloggen. Nya rader läggs sist. Låt filen ligga kvar.
MELACS.BAK är samma logg med en ny rad högst en gång i timmen. Den filen byts inte ut.
MELACS.SAF är säkerhetshändelser. Rock 5B hämtar dem och kvitterar, så en nätglitch tappar dem inte.
README.TXT och MELACS.ZIP skrivs bara om de saknas.
Ta bort zip-filen och starta om kortet om paketet ska skrivas igen.
