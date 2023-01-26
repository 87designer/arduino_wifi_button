// ---------------------------
// Multi-Button Controller
// ---------------------------

#include <OneButton.h>  // Button Library

// ---------------------------
// VARIABLES
// ---------------------------

const int yelBtnPin = 12;
const int redBtnPin = 11;
const int grnBtnPin = 10;
const int bluBtnPin = 9;

// ---------------------------

OneButton yelButton(yelBtnPin, true);
OneButton redButton(redBtnPin, true);
OneButton grnButton(grnBtnPin, true);
OneButton bluButton(bluBtnPin, true);

// ---------------------------

int LEDPin = 7;

// ---------------------------

String wet = "Wet-Diaper";
String dirty = "Dirty-Diaper";
String mixed = "Mixed-Diaper";
String feeding = "Feeding";
String sleepWake = "Sleep-Wake";

// ---------------------------


// ---------------------------
// SETUP
// ---------------------------

void setup() {
  Serial.begin(9600);

  pinMode(yelBtnPin, INPUT);
  pinMode(redBtnPin, INPUT);
  pinMode(grnBtnPin, INPUT);
  pinMode(bluBtnPin, INPUT);
  pinMode(LEDPin, OUTPUT);

  yelButton.attachDoubleClick(yelDoubleclick);

  redButton.attachDoubleClick(redDoubleclick);
  redButton.attachLongPressStart(redLongclick);

  grnButton.attachDoubleClick(grnDoubleclick);

  bluButton.attachDoubleClick(bluDoubleclick);

}

// ---------------------------


// ---------------------------
// LOOP
// ---------------------------

void loop () {

  // Establish Button logic here
  yelButton.tick();
  redButton.tick();
  grnButton.tick();
  bluButton.tick();

  // 
  delay(10);

}

// ---------------------------


// ---------------------------
// LED BLINK MODES
// ---------------------------

void singleBlinkLED(){
    digitalWrite(LEDPin, HIGH);
    delay(500);
    digitalWrite(LEDPin, LOW);
    }

// ---------------------------

void doubleBlinkLED(){
    digitalWrite(LEDPin, HIGH);
    delay(100);
    digitalWrite(LEDPin, LOW);
    delay(100);
    digitalWrite(LEDPin, HIGH);
    delay(100);
    digitalWrite(LEDPin, LOW);
    delay(100);
    }

// ---------------------------

void longBlinkLED(){
    digitalWrite(LEDPin, HIGH);
    delay(2000);
    digitalWrite(LEDPin, LOW);
    }

// ---------------------------


// ---------------------------
// BUTTONS
// ---------------------------

void yelDoubleclick() {
  Serial.println(wet);
  doubleBlinkLED();
}

// ---------------------------

void redDoubleclick() {
  Serial.println(dirty);
  doubleBlinkLED();
}

// ---------------------------

void redLongclick(){
  Serial.println(mixed);
  longBlinkLED();
}

// ---------------------------

void grnDoubleclick() {
  Serial.println(feeding);
  doubleBlinkLED();
}

// ---------------------------

void bluDoubleclick() {
  Serial.println(sleepWake);
  doubleBlinkLED();
}

// ---------------------------
