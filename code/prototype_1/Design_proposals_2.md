---
geometry: margin=2.5cm
---

<!--

Detta dokument skiljer sig från Design_proposals.md genom att ny information
kring hur hanteringen av CAN-buss har framkommit.

-->

<!-- Table of contents ovan -->
\newpage

#Förslag för implementationslösning

Följande är idéer om hur vi ska gå tillväga för att implementera 
optionshanteringen både på nuvarande MCU och nya OCU.

##Inledning
Meddelanden mellan OCU och MCU skickas taktat med PDO^[Process Data Object]-meddelanden. Anledningen
till detta är att meddelanden måste komma fram deterministiskt. Att skicka SDO
skulle leda till osäkerhet kring när paket kommer fram då de är lägst prioriterade.

##Funktionsprimitiver
Ett antal funktionsprimitiver måste identifieras för MCU. Dessa ska tillgänglig-
göras över CAN-bussen. En tidig tanke var att genom ett dynamiskt protokoll
anropa dessa funktioner från OCU och sedan behandla funktionsanropen på MCU.
Detta koncept får skrotas eftersom detta skulle ta en alldeles för stor bit
av den tillgängliga bandbredden, samt kan vara lite odeterministisk och svår-
testat.

Detta kommer innebära att vi konstruerar ett antal förbestämda register som
motsvarar de PDO-paket vi ska skicka. Dessa register kapslas sedan av funktioner
som sätter data i korrekt byte för att underlätta för programmeraren.

##Realtidssignaler
De flesta realtidssignaler finns redan representerade på CAN-bussen - det handlar
om att läsa in dessa för att minska på nödvändig bandbredd. Fyra CAN-meddelanden
under 20 ms är 25 % av bandbredden. OCU kommer därför att avläsa information som
skickas mellan ACT och MCU.

Signalerna kommer att skickas som olika PDO-objekt. Dessa är fördefinierade och
både MCU och OCU vet vad dessa betyder. Det är också implicit att dessa skickas
varje loop (20:e ms). Det kanske kan te sig onödigt att skicka dessa värden hela
tiden, ur bandbreddssynpunkt, eftersom de inte alltid ändras. Detta är en _kostnad_
som tas för att få ett deterministiskt beteende.

PDO-objekten delas upp enligt följande:

 - PDOrx1 - Objekt som innehåller input från knappar och liknande. Skickas från
   MCU till OCU.
 - PDOtx1 - Innehåller begränsning/önskat värde av hastighet, hydraulik och andra
   driv-egenskaper. Skickas frånOCU till  MCU.
 - PDOtx2 - Innehåller displaydata. Skickas från OCU till MCU.

Det kan tillkomma fler objekt, och objektens funktion kan komma att ändras.

<!--

VIKTIGT: Väldigt mycket data existerar redan på CAN-bussen. OCU måste därför ha
förmågan att avlyssna denna och mappa upp korrrekt i interna register.

Michael tar fram ett interface för dataobjekten, färdigt denna vecka (v13).


-->

#Programloop
Beskrivning över respektive enhets huvudprogramloop.

##MCU

##OCU