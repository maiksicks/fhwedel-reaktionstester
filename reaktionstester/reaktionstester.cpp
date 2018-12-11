/*
  reaktionstester.cpp - Bibliothek für Reaktionstests
  Erstellt von Maik Sicks am 11.12.2018
*/

#include "Arduino.h"
#include "reaktionstester.h"

Reaktionstester::Reaktionstester(int _button, int _leds[], int _ledsCount) {

  button = _button;
  leds = _leds;
  ledsCount = _ledsCount;

  for (int i = 0; i < ledsCount; i++) {
    pinMode(_leds[i], OUTPUT);
  }
  
}

void Reaktionstester::setTestMode(boolean _testmode) {
  testmode = _testmode;
}

void Reaktionstester::setRandomReactionTime(int _minTime, int _maxTime) {
  minTime = _minTime;
  maxTime = _maxTime;
}

void Reaktionstester::setInvertLedPins(boolean _invertLeds) {
  invertLeds = _invertLeds;
}

void Reaktionstester::setInvertButtonPin(boolean _invertButton) {
  invertButton = _invertButton;
}

void Reaktionstester::setDebugOverSerial(boolean _enable, int _port) {
  debugging = _enable;
  serialport = _port;
}

void Reaktionstester::setDebugOverSerial(boolean _enable) {
  debugging = _enable;
}

void Reaktionstester::setScoreOutputType(String _type) {
  if (_type == "exact") {
    scoreOutputType = 2;
  } else {
    scoreOutputType = 1;
  }
}

void Reaktionstester::setStartAnimation(int _anim) {
  anim = _anim;
}

void Reaktionstester::runStartAnimation() {
  Serial.println("runStartAnimation(" + (String) anim + ")");
  
  switch (anim) {
    case 1:
      boolean initEnd = false;
      int current = 0;
      int next = 1;
      int wait = 0;
      
      while (!initEnd) {
        if ((current + 1) == ledsCount) {
          next = -1;
        } else if (current == 0){
          next = 1;
        }

        ledOff(current);
        current += next;
        ledOn(current);

        delay(wait);
        wait++;

        if (wait == 71) {
          initEnd = true;
        }
      }
      break;
  }

  allLedsOff();
}

void Reaktionstester::init() {
  if (debugging) {
    Serial.begin(serialport);
    Serial.println("Debugging has started.");
  }

  if (testmode) {
    if (debugging)
      Serial.println("Testmode enabled.");
    
    runTestMode();
  }
  
  runStartAnimation();
  hasStarted = true;
}

void Reaktionstester::runTestMode() {

  // all leds on?
  allLedsOn();
  delay(1000);
  allLedsOff();
  delay(2000);

  // all leds in the right order?
  for (int i = 0; i < ledsCount; i++) {
    ledOn(i);
    delay(500);
    ledOff(i);
  }
  delay(2000);

  // is the button working?
  testModeMenuOutput(0);
  allLedsOn();
  waitForButtonPress();
  allLedsOff();
  waitForButtonRelease();

  // run start animation
  testModeMenuOutput(1);
  runStartAnimation();

  // run reaction test
  testModeMenuOutput(2);
  scoreOutputType = 2; // exact
  runReactionTestCountdown();

  // start normally
  testModeMenuOutput(3);
  scoreOutputType = 1; // normal
  // (... when leaving this function)
}

void Reaktionstester::testModeMenuOutput(int _menu) {
  for (int i = 0; i <= _menu; i++) {
    ledOn(i);
  }
  delay(1000);
  allLedsOff();
  delay(500);
}

void Reaktionstester::runListener() {
  if (hasStarted) {
    if (isButtonPressed()) {
      Serial.println("Button pressed, waiting for release...");
      waitForButtonRelease();
      Serial.println("Button released, start reaction tester");
      runReactionTestCountdown();
    }
    
  } else {
    if (debugging)
      Serial.println("Error: run init() before runListener()");
  }
}

void Reaktionstester::runReactionTestCountdown() {
  allLedsOn();
  delay(100);
  allLedsOff();
  delay(900);
  
  allLedsOn();
  delay(100);
  allLedsOff();
  delay(900);
  
  allLedsOn();
  delay(1000);
  allLedsOff();

  runReactionTest();
}

void Reaktionstester::runReactionTest() {
  waitForButtonRelease();

  // wait {random} milliseconds
  int randomTime = random(minTime, maxTime); 
  delay(randomTime);

  // save reaction start time
  int startTime = millis();

  if (isButtonPressed()) {
    if (debugging)
      Serial.println("Button is pressed, before LEDs were turned on!");
      
    printTestScore(10000);
  } else {
    allLedsOn();
    waitForButtonPress();
    int score = millis() - startTime;
    allLedsOff();
    waitForButtonRelease();
    printTestScore(score);
  }
  
}

void Reaktionstester::printTestScore(int _score) {
  if (debugging)
    Serial.println("Score: " + (String) _score);
    
  switch(scoreOutputType) {
    case 1:

      if (_score < 200) {
        for (int i = 0; i < ledsCount; i++) {
          ledOn(i);
          delay(100);
        }
        for (byte i = 0; i < 5; i++) {
          allLedsOff();
          delay(150);
          allLedsOn();
          delay(150);
        }
    
      } else if (_score < 300) {
        for (int i = 0; i < (ledsCount - 1); i++) {
          ledOn(i);
          delay(100);
        }
      } else if (_score < 400) {
        for (int i = 0; i < (ledsCount - 2); i++) {
          ledOn(i);
          delay(100);
        }
      } else if (_score < 500) {
        for (int i = 0; i < (ledsCount - 3); i++) {
          ledOn(i);
          delay(100);
        }
      } else if (_score < 600) {
        for (int i = 0; i < (ledsCount - 4); i++) {
          ledOn(i);
          delay(100);
        }
      } else if (_score < 700) {
        for (int i = 0; i < (ledsCount - 5); i++) {
          ledOn(i);
          delay(100);
        }
      } else {
        for (int i = 0; i < (ledsCount - 6); i++) {
          ledOn(i);
          delay(100);
        }
      }

      delay(5000);
      allLedsOff();
      
      break;
    case 2:
      if (_score > 9999) {
        allLedsOn();
        delay(3000);
      } else {
      
        int digit_1 = _score / 1000;
        int digit_2 = _score % 1000 / 100;
        int digit_3 = _score % 100 / 10;
        int digit_4 = _score % 10;
    
        ledBlink(ledsCount - 4, digit_1);
        delay(1000);
        ledBlink(ledsCount - 3, digit_2);
        delay(1000);
        ledBlink(ledsCount - 2, digit_3);
        delay(1000);
        ledBlink(ledsCount - 1, digit_4);
        delay(1000);
    
        allLedsOn();
        delay(1000);
        
      }
    
      allLedsOff();
      delay(1000);
      break;
  }
}

// LED functions

void Reaktionstester::ledBlink(int _led, int _count) {
  for (int i = 0; i < _count; i++) {
      ledOn(_led);
      delay(250);
      ledOff(_led);
      delay(250);
    }
}

void Reaktionstester::ledOn(int _led) {
  if (debugging)
    Serial.println("ledOn(" + (String) _led + ")");
  digitalWrite(leds[_led], (invertLeds ? LOW : HIGH));
}

void Reaktionstester::allLedsOn() {
  if (debugging)
    Serial.println("allLedsOn()");
  for (int i = 0; i < ledsCount; i++) {
    digitalWrite(leds[i], (invertLeds ? LOW : HIGH));
  }
}

void Reaktionstester::ledOff(int _led) {
  if (debugging)
    Serial.println("ledOff(" + (String) _led + ")");
  digitalWrite(leds[_led], (invertLeds ? HIGH : LOW));
}

void Reaktionstester::allLedsOff() {
  if (debugging)
    Serial.println("allLedsOff()");
  for (int i = 0; i < ledsCount; i++) {
    digitalWrite(leds[i], (invertLeds ? HIGH : LOW));
  }
}

// Button functions
boolean Reaktionstester::isButtonPressed() {
  boolean val = digitalRead(button);
  return (invertButton ? (val == HIGH) : (val == LOW));
}

void Reaktionstester::waitForButtonRelease() {
  while (isButtonPressed()) {
    1;  
  }
}

void Reaktionstester::waitForButtonPress() {
  while (!isButtonPressed()) {
    1;  
  }
}


