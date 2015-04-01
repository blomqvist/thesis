---
geometry: margin=2.5cm
---


\newpage

#TODO-lista

Checklist för vad som ska implementeras

 - ICH: app.c Startup_OCU_Done = startup_OCU_(); // _OCU_ flytta ut ur BENCH_BUILD [ ]

 - Initiera Can-interface: void gw_initializeMcu() i `mcu.c` [X]
    - Tilldela rätt ID, DLC osv
 - PDOrx ska modifieras på OCU. preApplicationFunctions() i `system.c`[X]
    - Lägga till lyssning på `rx`-objektet
    - Lägga in data från `rx`-objektet i buffert
 - PDOtx ska modifieras på OCU. RunApplication() i `mcu.c` [X]
    - Lägga till `tx`-buffert
    - Lägga till funktioner som abstraherar skrivning till korrekt fält
    - sendMcuPdo() i mcu.c behöver städas från PWM debugg
 - Avlyssning av CAN-buss för ACT-/EPS-data [ ]
    - Från _CANopen mapping.doc_ avgöra vilka PDO-objekt som är relevanta [ ]
    - Implementera avlyssning av dessa objekt [ ]
 - Stöd för optioner i egenskap av funktion som kan anropa dom [ ]
    - Genomtänkt placering av optionfilsmapp [ ]
    - Förbereda för skript som kan generera optioner från simplare syntax [ ]
    - Lösa en syntax som är simplare än C, men tillräcklig för vad som ska
      lösas
 - Aktivera io: [ ]
    - ingen Can-kommunikation är nödvändig här
    - via optioner [ ]
    - som spider? [ ]
 - App.c: Pulserar Pwm på io, tabort det? [X] 
    - void updateApplication()


Skrota Signal array. läsa direkt från can buffert istället


Tillvägagångssätt för implementations:
1: postApplication. Skicka pseudofunktionsanrop till mcu. validera med canalyzer.

2: preApplication. Ta emot realtidsvärden från mcu. valideras med testbänk.

3: runOptions. loop för uträkning av villkor. Input och output är fastställt
   vid det här skedet enligt 1 & 2. 


#Dokumentation
Allmän snabbdokumentation för att lättare hitta

##PDO-objekt
Vart befinner sig PDO-objektet. Vilka filer?

`gw_preApplicationMcu`:  
Implementation av mottagning av data som skickas från MCU. `PDOrx` ska läsas in
här.

###ACT
ACT har ID 8, 10 eller 11.
Vilka är relevanta?

För PDO-objekt med COB ID is 0x180 + ACT CANopen ID erhålls följande

 - 0..1 - Status word (Status word bit)
 - 2..3 - Traction Actual Speed
 - 4..5 - Pump Output DC Current
 - 6..7 - Digital Input Status

Mer information om dessa i _CANopen mapping.doc_

###EPS
Har CANopen ID 7

##Syntax?