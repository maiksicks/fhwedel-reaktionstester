// CONFIG BELOW

const int firstLed = 6;
const int lastLed = 12;

// set test mode
const boolean testmode = true;

// PROGRAM CODE BELOW

int countdown = 0;
int reaction = 0;

boolean off = true;

void setup() {
  // set all led pinouts
  for (int i = firstLed; i <= lastLed; i++) {
    pinMode(i, OUTPUT);
  }


  if (testmode) {
    test();
  } else {
    // start-animation
    start();
  }
}

void test() {
  // test all LEDs working
  allLedOn(firstLed, lastLed);
  delay(1000);
  allLedOff(firstLed, lastLed);
  delay(1000);

  // test each LED working
  for (int i = firstLed; i <= lastLed; i++) {
    digitalWrite(i, HIGH);
    delay(1000);
    digitalWrite(i, LOW);
  }
  delay(1000);


  // test switch working
  test_menu_indicator(0);
  allLedOn(firstLed, lastLed);
  while (digitalRead(2) == LOW) {
    1;
  }
  allLedOff(firstLed, lastLed);
  delay(1000);

  // test start animation
  test_menu_indicator(1);
  start();
  delay(1000);

  // set reaction test to exact output and start it
  test_menu_indicator(2);
  startReaction();

  test_menu_indicator(3);
  // start normally with exact output
}

void test_menu_indicator(int menu) {
  for (int i = firstLed; i <= firstLed + menu; i++) {
    digitalWrite(i, HIGH);
  }
  delay(1000);
  allLedOff(firstLed, lastLed);
  delay(500);
}

void start() {
  boolean initEnd = false;
  int cur = firstLed;
  int next = 1;
  int wait = 1;
  
  while (!initEnd) {
    allLedOff(firstLed, lastLed);
    digitalWrite(cur, HIGH);
    
    cur += next;
    
    if (cur >= lastLed || cur <= firstLed) {
      next = -next;
    }

    delay(wait);

    wait = wait + 1;

    if (wait == 74) {
      allLedOff(firstLed, lastLed);
      initEnd = true;
    }
  }
}

void allLedOff(int fe, int le) {
  for (int i = fe; i <= le; i++) {
    digitalWrite(i, LOW);
  }
}

void allLedOn(int fe, int le) {
  for (int i = fe; i <= le; i++) {
    digitalWrite(i, HIGH);
  }
}

void startReaction() {

  // wait, until button is released
  while (digitalRead(2) == HIGH) {
    1;
  }

  // wait {random} milliseconds
  int randomTime = random(500, 5000); 
  delay(randomTime);

  // save reaction start time
  int startTime = millis();
  allLedOn(firstLed, lastLed);

  // wait, until button is pressed
  while (digitalRead(2) == LOW) {
    1;
  }

  allLedOff(firstLed, lastLed);

  // calculate score (reaction time in milliseconds)
  int score = millis() - startTime;

  delay(500);

  if (testmode) {
    print_score_exactly(score);
  } else {
    print_score_userfriendly(score);
  }
}

void print_score_exactly(int score) {
  if (score > 9999) {
    allLedOn(firstLed, lastLed);
    delay(3000);
  } else {
  
    int digit_1 = score / 1000;
    int digit_2 = score % 1000 / 100;
    int digit_3 = score % 100 / 10;
    int digit_4 = score % 10;

    ledBlink(lastLed - 3, digit_1);
    delay(1000);
    ledBlink(lastLed - 2, digit_2);
    delay(1000);
    ledBlink(lastLed - 1, digit_3);
    delay(1000);
    ledBlink(lastLed, digit_4);
    delay(1000);

    allLedOn(firstLed, lastLed);
    delay(1000);
    
  }

  allLedOff(firstLed, lastLed);
  delay(1000);
  
}

void ledBlink(int led, int count) {
  for (int i = 0; i < count; i++) {
      digitalWrite(led, HIGH);
      delay(250);
      digitalWrite(led, LOW);
      delay(250);
    }
}

void print_score_userfriendly(int score) {
  
  if (score < 200) {
    for (byte i = firstLed; i <= lastLed; i++) {
      digitalWrite(i, HIGH);
      delay(100);
    }
    for (byte i = 0; i < 5; i++) {
      allLedOff(firstLed, lastLed);
      delay(150);
      allLedOn(firstLed, lastLed);
      delay(150);
    }

  } else if (score < 300) {
    for (byte i = firstLed; i <= (lastLed - 1); i++) {
      digitalWrite(i, HIGH);
      delay(100);
    }
  } else if (score < 400) {
    for (byte i = firstLed; i <= (lastLed - 2); i++) {
      digitalWrite(i, HIGH);
      delay(100);
    }
  } else if (score < 500) {
    for (byte i = firstLed; i <= (lastLed - 3); i++) {
      digitalWrite(i, HIGH);
      delay(100);
    }
  } else if (score < 600) {
    for (byte i = firstLed; i <= (lastLed - 4); i++) {
      digitalWrite(i, HIGH);
      delay(100);
    }
  } else if (score < 700) {
    for (byte i = firstLed; i <= (lastLed - 5); i++) {
      digitalWrite(i, HIGH);
      delay(100);
    }
  } else {
    for (byte i = firstLed; i <= (lastLed - 6); i++) {
      digitalWrite(i, HIGH);
      delay(200);
    }
  }
  
  delay(5000);
  off = true;
  allLedOff(firstLed, lastLed);
}

void loop() {

  if (off) {

    // wait for button press
    if (digitalRead(2) == HIGH) {
      off = false;
    }
    delay(50);

    countdown = 8;
    
  } else {

    // play ready-set-go animation
    if (countdown == 8) {
      allLedOn(firstLed, lastLed);
    } 

    if (countdown == 6) {
      allLedOff(firstLed, lastLed);
      allLedOn(firstLed + 1, lastLed - 1);
    }

    if (countdown == 4) {
      allLedOff(firstLed, lastLed);
      allLedOn(firstLed + 2, lastLed - 2);
    } 

    if (countdown == 2) {
      allLedOff(firstLed, lastLed);
      allLedOn(firstLed + 3, lastLed - 3);
    } 

    if (countdown == 0) {
      allLedOff(firstLed, lastLed);
      startReaction();
    } 
    
    if (countdown > 0) {
      countdown--;
      delay(500);
    }
    
  }
  
}

