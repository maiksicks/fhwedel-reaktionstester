# Reaktionstester

![Bild](https://raw.githubusercontent.com/maiksicks/fhwedel-reaktionstester/master/images/reaktionstester_steckplatine.png)

## Aufgabe

Das Ziel der Veranstaltung "Eingebettete Software" ist der Bau eines Reaktionstesters. Dieser soll mit Hilfe eines Tasters geweckt werden und einen Test starten. Der Reaktionstest findet ebenfalls mit dem Einschalttaster statt. Das Ergebnis wird anschließend LEDs ausgegeben. 

Grundlage des Reaktionstesters ist ein Arduino UNO. Der Tester soll auf einem Steckbrett aufgebaut werden. Quellcode und Schaltplan inkl. Funktionsbeschreibung und Weiterentwicklungsmöglichkeiten sollen öffentlich auf einem Repository liegen.

## Vorraussetzungen

**Inbetriebnahme**

- Arduino über USB mit Strom versorgen und Spaß haben.

**Nachbau**

- Material: Arduino UNO, diverse Kabel, Steckbrett, 7 LEDs, 7x 220Ω Widerstand, 1x 10kΩ Widerstand, Computer mit USB-Anschluss (zur einmaligen Installation der Software)
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

## Wartung

Der Reaktionstester ist wartungsfrei. 

## Weiterentwicklung

**Verbesserung der Ausgabe**
- LCD Display
- Audioausgabe
- Farbige LEDs

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
