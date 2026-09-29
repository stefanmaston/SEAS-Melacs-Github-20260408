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
och safe_mode (%MW0) är 0. 1 betyder säkra utgångar.

MELACS.CSV på det här kortet är dataloggen. Låt den ligga kvar.
README.TXT och MELACS.ZIP skrivs bara om de saknas.
Ta bort zip-filen och starta om kortet om paketet ska skrivas igen.
