#Prosjekt Rapport

Produsert av: [Joakim Pettersvold (Joakim1999)](https://github.com/joakim1999) og [Daniel Løvbrøtte Olsen (Dali99)](https://github.com/dali99)

Ansvarlig lærer: Frank Roy Jensen

Denne rapporten blir skrevet for en obligatorisk prosjektoppgave vi har fått i faget Data og Elektronikk. Vi valgte å lage en avstandsmåler.

# Materiell
Til dette prosjektet visste vi at vi trengte:
* Ultrasoniske sensor (HC-SR04)
* En mikrokontroller (Arduino Uno)
* Et serielt display (QAPASS 1602A med I2C chip)
* Ledere

#Oppbygning
Det første vi gjorde var å koble vcc og gnd på den ultrasoniske sensoren og vcc og gnd på I2C kretsen til hver sin 5V og ground på Arudionoen.
Deretter koblet vi fra SDA og SCL fra I2C kretsen til A4 og A5 på Arduinoen.
Skjermen vi har valgt er egentlig SPI, men siden det hadde krevd mye mer GPIO valgte vi å bruke I2C.
I2C er en kommunikasjonsprotokoll som lar oss gjøre om to analoge signaler til SPI, dette reduserer båndbredden, men den største sakningen ligger i skjermen.

#Feilsøkning
Å få til dette prosjektet gikk relativt smertefritt og gikk også relativt raskt. 
Likevel var det ting som måtte feilsøkes.
Det første problemet vi støtte på var at den serielle skjermen skrudde seg på men ikke viste noe tekst, selv om den var programmert til å gjøre det.
Vi prøvde å feilsøke kildekoden for å se om det var noe feil med den, men vi kunne ikke finne noen feil.
Vi fant ut etter å se veldig nøye på displayet at teksten faktisk sto der men at kontrasten var veldig dårlig.
Vi visste ikke hvordan vi kunne endre kontrasten før etter litt da vi fant ut at det var et lite potensiometer på I2C kretsen.
Når vi justerte potensiometeret kom teksten frem med en gang.

Den andre feilsøkingen vi måtte gjøre var når den serielle skjermen viste helt feil resultater.
Etter litt tenkning kom vi frem til at skjermen ikke ble ble tømt automatisk og at det var derfor det tredje tallet “ghostet”, altså forble på skjermen.
Dette gjorde at hvis du målte noe som var 100+cm langt, ville den siste nullen forbli når du målte neste objekt, som kansje bare er 3cm, resultatet var at det så ut som 300cm.
Vi fant også ut at vi ikke hadde en funksjon for å tømme skjermen i programmet vårt.
Vi eksperimenterte litt med hvordan vi skulle få til dette.
Først printet vi 16 mellomrom til skjermen mellom hver skriving, men dette var veldig tregt.
Bare tre mellomrom fungerte mye bedre, men vi så irriterende blinking.
Da slo det oss å bruke “sprintf format spesifikatorer”. “sprintf” er en standard funksjon som lar deg printe tekst eller tall til en peker, og spesifikatorene lar deg for eksempel polstre tall til å ha nuller foran.
Så i stedet for 1, blir det 001, og i stedet for 10 blir det 010.
Dette lar oss bare printe en gang til skjermen, men fortsatt oppdatere alle tre sifferene.

Etter det var det bare noen justeringer igjen.
Vi så at målingen dirret, dette ble løst ved å ta median målingen av fem målinger i stedet for å vise “real time” måling.
Det går fortsatt rast nok til at det ikke merkes, og reduserte skjerm blinke problemet enda mer.

#Krav
* [NewPing](https://bitbucket.org/teckel12/arduino-new-ping/ vi har brukt v1.7)
* [NewLiquidCrystal](https://bitbucket.org/fmalpartida/new-liquidcrystal/wiki/Home)
