// ---------------------------
// Multi-Button Controller
// ---------------------------

#include <OneButton.h>  // Button Library

// ---------------------------
// VARIABLES
// ---------------------------
const int btn1Pin = 2;
const int btn2Pin = 3;
const int btn3Pin = 4;
const int btn4Pin = 5;

int red = 9;
int green = 10;
int blue = 11;

OneButton btn1(btn1Pin, true);
OneButton btn2(btn2Pin, true);
OneButton btn3(btn3Pin, true);
OneButton btn4(btn4Pin, true);

String wet = "Wet-Diaper";
String dirty = "Dirty-Diaper";
String mixed = "Mixed-Diaper";
String feeding = "Feeding";
String sleepWake = "Sleep-Wake";

int redLED[]={125,0,0};
int greenLED[]={0,125,0};
int blueLED[]={0,0,125};
int* colorStatus=redLED;
// ---------------------------

void RGB_color(int red_value, int green_value, int blue_value) {
  // custom function to set three PWM color channels to any given mixture
  analogWrite(red, red_value);
  analogWrite(green, green_value);
  analogWrite(blue, blue_value);
}

void setup() {
  Serial.begin(115200);

  pinMode(red, OUTPUT);
  RGB_color(colorStatus[0],colorStatus[1],colorStatus[2]);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);

  pinMode(btn1Pin, INPUT);
  pinMode(btn2Pin, INPUT);
  pinMode(btn3Pin, INPUT);
  pinMode(btn4Pin, INPUT);

  btn1.attachDoubleClick(doubleClick1);
  btn2.attachDoubleClick(doubleClick2);
  btn2.attachLongPressStart(longClick2);
  btn3.attachDoubleClick(doubleClick3);
  btn4.attachDoubleClick(doubleClick4);
}

void loop () {
  if (Serial.available()) {
    String wifiStatus = Serial.readStringUntil('\r\n');
    wifiStatus.trim();
    if (wifiStatus == "Y") {
      colorStatus = greenLED;
      RGB_color(colorStatus[0],colorStatus[1],colorStatus[2]);
    } if (wifiStatus == ".") {
      colorStatus = redLED;
      RGB_color(colorStatus[0],colorStatus[1],colorStatus[2]);
    }
  }

  // Establish Button logic here
  btn1.tick();
  btn2.tick();
  btn3.tick();
  btn4.tick();

  delay(10);
}

// ---------------------------
// LED BLINK MODES
// ---------------------------
void singleBlinkLED(){
    RGB_color(0, 0, 125); // Blue
    delay(100);
    RGB_color(0, 0, 0);
    delay(100);
    RGB_color(colorStatus[0],colorStatus[1],colorStatus[2]);
    }

void doubleRedBlinkLED(){
    RGB_color(125, 0, 0); // Blue
    delay(100);
    RGB_color(0, 0, 0);
    delay(100);
    RGB_color(125, 0, 0); // Blue
    delay(100);
    RGB_color(0, 0, 0);
    delay(100);
    RGB_color(colorStatus[0],colorStatus[1],colorStatus[2]);
    }

void doubleBlueBlinkLED(){
    RGB_color(0, 0, 125); // Blue
    delay(100);
    RGB_color(0, 0, 0);
    delay(100);
    RGB_color(0, 0, 125); // Blue
    delay(100);
    RGB_color(0, 0, 0);
    delay(100);
    RGB_color(colorStatus[0],colorStatus[1],colorStatus[2]);
    }

void longBlinkLED(){
    RGB_color(0, 0, 125); // Blue
    delay(1000);
    RGB_color(colorStatus[0],colorStatus[1],colorStatus[2]);
    }

// ---------------------------
// BUTTONS
// ---------------------------
void doubleClick1() {
  Serial.println(wet);
  doubleBlueBlinkLED();
}

void doubleClick2() {
  Serial.println(dirty);
  doubleBlueBlinkLED();
}

void longClick2(){
  Serial.println(mixed);
  longBlinkLED();
}

void doubleClick3() {
  Serial.println(feeding);
  doubleBlueBlinkLED();
}

void doubleClick4() {
  Serial.println(sleepWake);
  doubleBlueBlinkLED();
}
