/*
  reaktionstester.h - Bibliothek für Reaktionstests
  Erstellt von Maik Sicks am 11.12.2018
*/

#ifndef reaktionstester_h
#define reaktionstester_h

#include "Arduino.h"

class Reaktionstester {
  public:
    Reaktionstester(int _button, int _leds[], int _ledsCount);
    void setStartAnimation(int _anim);
    void setTestMode(boolean _testmode);
    void setRandomReactionTime(int _minTime, int _maxTime);
    void setInvertLedPins(boolean _invertLeds);
    void setInvertButtonPin(boolean _invertButton);
    void setDebugOverSerial(boolean _enable);
    void setDebugOverSerial(boolean _enable, int _port);
    void setScoreOutputType(String _type);
    void init();
    void runListener();
    
  private:
    void runStartAnimation();
    void ledOn(int _led);
    void allLedsOn();
    void ledOff(int _led);
    void ledBlink(int _led, int _count);
    void allLedsOff();
    void waitForButtonRelease();
    void waitForButtonPress();
    boolean isButtonPressed();
    void runReactionTestCountdown();
    void runReactionTest();
    void printTestScore(int _score);
    void runTestMode();
    void testModeMenuOutput(int _menu);

    int hasStarted = false;
    int button;
    int * leds;
    int ledsCount;
    boolean invertLeds;
    boolean invertButton;
    boolean testmode = false;
    int anim = 1; // default
    int minTime = 500;
    int maxTime = 5000;
    boolean debugging = false;
    int serialport = 9600;
    int scoreOutputType = 1;
};

#endif
