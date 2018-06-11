/*
  An I2C based LED Stick
  By: Ciara Jekel
  SparkFun Electronics
  Date: June 11th, 2018
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

  Feel like supporting our work? Buy a board from SparkFun!
  https://www.sparkfun.com/products/14783

  This example changes brightness of the LED Stick in different
  ways, then steps through each available brightness setting.

*/

#include "Qwiic_LED_Stick.h" // Click here to get the library: http://librarymanager/All#Sparkfun_Qwiic_LED_Stick

LED LEDStick;
//           Pixel#     1    2    3    4    5    6    7    8    9   10
byte redArray[10]   = {255, 255, 170,   0,   0,   0,   0, 170, 255, 255};
byte greenArray[10] = {  0, 170, 255, 255, 255, 170,   0,   0,   0, 255};
byte blueArray[10]  = {  0,   0,   0,   0, 170, 255, 255, 255, 170, 255};

void setup() {
  Serial.begin(9600);
  LEDStick.begin();
  //Colors the LEDStick with a rainbow, 10th pixel white
  LEDStick.setLEDColor(redArray, greenArray, blueArray, 10);
  //set brightness of all LEDS to about half of maximum brightness
  LEDStick.setLEDBrightness(16);
  delay(1000);
  //set brightness of tenth LED very low
  LEDStick.setLEDBrightness(10, 2);
  delay(1000);
}

void loop() {
  //This will step through each available brightness setting
  //Brightness values can be from 0-31
  for (byte i = 0; i < 32; i++) {
    //set brightness of all LEDs to value i
    LEDStick.setLEDBrightness(i);
    Serial.print("Brightness level: ");
    Serial.println(i);
    delay(1000);
  }
}

