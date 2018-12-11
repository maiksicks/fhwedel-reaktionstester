/*
  reaktionstester.ino - Reaktionstest
  Erstellt von Maik Sicks am 11.12.2018
*/

#include "reaktionstester.h"

int LED_PINS[] = {6, 7, 8, 9, 10, 11, 12};
int BUTTON_PIN = 2;
int LED_COUNT = 7; // min: 7

Reaktionstester rt(BUTTON_PIN, LED_PINS, LED_COUNT);

void setup() {

  // OPTIONAL: set test mode (default: false)
  rt.setTestMode(false);

  // OPTIONAL: set start animation (default: 1)
  rt.setStartAnimation(1);

  // OPTIONAL: set random reaction time (default: 500-5000)
  rt.setRandomReactionTime(500, 5000);

  // OPTIONAL: invert LED pins (HIGH => LOW, LOW => HIGH, default: false)
  rt.setInvertLedPins(false);

  // OPTIONAL: invert Button pin (false => pull-down, true => pull-up)
  rt.setInvertButtonPin(true);

  // OPTIONAL: enable debugging over serialport (default: false[, 9600])
  rt.setDebugOverSerial(false, 9600);

  // OPTIONAL: switch score output between "normal" and "exact" (default: "normal")
  rt.setScoreOutputType("normal");

  // REQUIRED: initalize
  rt.init();
}

void loop() {
  // REQUIRED: run
  rt.runListener();
}
