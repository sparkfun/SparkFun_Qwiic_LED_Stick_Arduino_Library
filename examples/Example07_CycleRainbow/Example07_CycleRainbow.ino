/*
  An I2C based LED Stick
  By: Ciara Jekel
  SparkFun Electronics
  Date: June 11th, 2018
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

  Feel like supporting our work? Buy a board from SparkFun!
  https://www.sparkfun.com/products/14783
  
  This example makes the LED Stick smoothly change through the colors of the rainbow.

*/

#include "Qwiic_LED_Stick.h" // Click here to get the library: http://librarymanager/All#Sparkfun_Qwiic_LED_Stick

LED LEDStick;

void setup() {
  Serial.begin(9600);
  LEDStick.begin();
}

void loop() {
  CycleRainbow(10);
}

//Cycle through the rainbow with all LEDs the same color
void CycleRainbow(int delayTime) {
  for (byte g = 0; g < 255; g++) {
    LEDStick.setLEDColor(255, g, 0);
    delay(delayTime);
  }
  for (byte r = 255; r > 0; r--) {
    LEDStick.setLEDColor(r, 255, 0);
    delay(delayTime);
  }
  for (byte b = 0; b < 255; b++) {
    LEDStick.setLEDColor(0, 255, b);
    delay(delayTime);
  }
  for (byte g = 255; g > 0; g--) {
    LEDStick.setLEDColor(0, g, 255);
    delay(delayTime);
  }
  for (byte r = 0; r < 255; r++) {
    LEDStick.setLEDColor(r, 0, 255);
    delay(delayTime);
  }
  for (byte b = 255; b > 0; b--) {
    LEDStick.setLEDColor(255, 0, b);
    delay(delayTime);
  }
}

