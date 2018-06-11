/*
  An I2C based LED Stick
  By: Ciara Jekel
  SparkFun Electronics
  Date: June 11th, 2018
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

  Feel like supporting our work? Buy a board from SparkFun!
  https://www.sparkfun.com/products/14783

  This example will display a linear gradient from one color to another on the LED Stick.

*/

#include "Qwiic_LED_Stick.h" // Click here to get the library: http://librarymanager/All#Sparkfun_Qwiic_LED_Stick

LED LEDStick;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  LEDStick.begin();
  byte r1 = 238, g1 = 49, b1 = 36;
  byte r2 = 66, g2 = 235, b2 = 23;
  colorGradient(r1, g1, b1, r2, g2, b2, 10);
}

void loop() {

}

//Display a linear gradient from color 1 (r1,g1,b1) to color 2 (r2,g2,b2) on LED strip of length LEDLength
void colorGradient(byte r1, byte g1, byte b1, byte r2, byte g2, byte b2, byte LEDLength) {
  float rStep = 0, gStep = 0, bStep = 0;
  LEDLength--; //one less color step than length of LEDs
  boolean r, g, b; //if true, r/g/b 2  > r/g/b 1
  if (r = r1 < r2) //sets r to the boolean result of r1<r2
    rStep = (r2 - r1) / (float)LEDLength; //if r true
  else {
    rStep = (r1 - r2) / (float)LEDLength; //if r false
  }
  if (g = g1 < g2) //sets g to the boolean result of g1<g2
    gStep = (g2 - g1) / (float)LEDLength; //if g true
  else {
    gStep = (g1 - g2) / (float)LEDLength; //if g false
  }
  if (b = b1 < b2)//sets b to the boolean result of b1<b2
    bStep = (b2 - b1) / (float)LEDLength; //if b true
  else {
    bStep = (b1 - b2) / (float)LEDLength; //if b false
  }
  //+ or - depends on whether r/g/b2 > r/g/b1
  for (byte i = 0; i <= LEDLength; i++) {
    byte rValue = r ? r1 + rStep * i : r1 - rStep * i; //uses + operation if r true, - if false
    byte gValue = g ? g1 + gStep * i : g1 - gStep * i; //uses + operation if g true, - if false
    byte bValue = b ? b1 + bStep * i : b1 - bStep * i; //uses + operation if b true, - if false
    LEDStick.setLEDColor(i + 1, rValue, gValue, bValue);
  }
}

