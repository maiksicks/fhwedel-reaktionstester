# Reaktionstester

**Letztes Update: 11.12.2018**

![Bild](https://raw.githubusercontent.com/maiksicks/fhwedel-reaktionstester/master/images/reaktionstester_steckplatine.png)

## Aufgabe

Das Ziel der Veranstaltung "Eingebettete Software" ist der Bau eines Reaktionstesters. Dieser soll mit Hilfe eines Tasters geweckt werden und einen Test starten. Der Reaktionstest findet ebenfalls mit dem Einschalttaster statt. Das Ergebnis wird anschließend LEDs ausgegeben. 

Grundlage des Reaktionstesters ist ein Arduino UNO. Der Tester soll auf einem Steckbrett aufgebaut werden. Quellcode und Schaltplan inkl. Funktionsbeschreibung und Weiterentwicklungsmöglichkeiten sollen öffentlich auf einem Repository liegen.

## Vorraussetzungen

**Inbetriebnahme**

- Arduino über USB mit Strom versorgen und Spaß haben.

**Nachbau**

- Material: Arduino UNO, diverse Kabel, Steckbrett, 7 LEDs, 7x 220Ω Widerstand, 1x 10kΩ Widerstand, Taster (NO), Computer mit USB-Anschluss (zur einmaligen Installation der Software)
- Software: z.B.: [Arduino IDE](https://www.arduino.cc/en/Main/Software)

**Weiterentwicklung**

- _Alle von "Nachbau"_
- Grundlegende Programmierkenntnisse in C++
- Grundlegende Kenntnisse in Elektronik
- Spaß am Rumprobieren und Geduld

## Funktionsweise

Wenn der Arduino über USB mit Strom versorgt wird, spielt er eine Willkommensanimation ab, welche auf den 7 angeschlossenen LEDs angezeigt wird. Das Ende der Animation erkennt man, wenn alle LEDs erloschen sind.

Ab diesem Punkt ist der Reaktionstester bereit. Um eine Messung zu starten, muss der Taster einmal betätigt werden. Danach läuft eine Countdown-Animation ab. Nach dem Countdown (alle LEDs sind aus) startet der Reaktionstest, denn sobald alle LEDs sich wieder einschalten, muss schnellstmöglich der Taster gedrückt werden.

Das Ergebnis wird ebenfalls mit Hilfe der LEDs angezeigt:

7 LEDs => 0-200ms<br>
6 LEDs => 200-300ms<br>
5 LEDs => 300-400ms<br>
...<br>
1 LED => ab 700ms

Das Ergebnis wird 5 Sekunden lang angezeigt, danach schalten sich die LEDs aus und man kann einen neuen Test starten, in dem man den Taster drückt.

## Einstellungen

**setTestMode**(<bool>testmode) 
(de)aktiviert den Testmodus. 

## Wartung

**Der Reaktionstester ist wartungsfrei.** Wer jedoch trotzdem testen möchte, kann die in der Setter-Methode **rt.setTestMode()** eingetragene Variable auf **true** setzen.

Nach dem Überspielen wird eine Testfunktion ausgeführt, mit der man alle Ein- und Ausgaben prüfen kann.

_Die Tests 1 bis 4 werden durch das Leuchten von entsprechend vielen LEDs signalisiert._

- Test 0 => Alle LEDs leuchten gleichzeitig, danach leuchten alle LEDs nacheinander in der richtigen Reihenfolge.
- Test 1 => Prüfung des Taster. Alle LEDs leuchten, bis der Taster gedrückt wurde.
- Test 2 => Prüfung der Startanimation (einfacher Durchlauf).
- Test 3 => Reaktionstest mit geänderter Ausgabe: Die Ausgabe erfolgt durch blinkende LEDs: Die 4 ersten LEDs stehen für die Ziffern einer Zahl. Blinken die Lampen folgendermaßen: (1x)(2x)(7x)(9x) ergibt dieses die Reaktionszeit in Millisekunden: 1279
- Test 4 => Normaler Reaktionstester-Betrieb (kann beliebig oft wiederholt werden).

## Weiterentwicklung

**Verbesserung der Ausgabe**
- LCD Display
- Audioausgabe
- Farbige LEDs
- Weitere Startanimation

**Verbesserung des Aufbaus**
- Löten einer Platine
- Gehäuse

**Änderung der Eingabe**
- Mehrere Taster
- Touch-Display

**Änderung der Funktionsweise**
- Challenge Mode (Mehrspieler)
- Online Score-Abgleich
- Statistiken
- Andere Reaktionstest-Art (z.B.: Taster nur drücken, wenn 2 LEDs leuchten)
