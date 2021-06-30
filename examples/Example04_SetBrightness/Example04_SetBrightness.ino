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

#include <Wire.h>
#include "Qwiic_LED_Stick.h" // Click here to get the library: http://librarymanager/All#SparkFun_Qwiic_LED_Stick

LED LEDStick; //Create an object of the LED class

//Create 3 arrays the same length as the LED stick,
//Initializing them as a rainbow followed by 1 white pixel
//           Pixel#     1    2    3    4    5    6    7    8    9   10
byte redArray[10]   = {255, 255, 170,   0,   0,   0,   0, 170, 255, 255};
byte greenArray[10] = {  0, 170, 255, 255, 255, 170,   0,   0,   0, 255};
byte blueArray[10]  = {  0,   0,   0,   0, 170, 255, 255, 255, 170, 255};

void setup() {
  Wire.begin();
  Serial.begin(115200);
  
  //Start up communication with the LED Stick
  if (LEDStick.begin() == false){
    Serial.println("Qwiic LED Stick failed to begin. Please check wiring and try again!");
    while(1);
  }

  Serial.println("Qwiic LED Stick ready!");

  //Start by resetting the state of the LEDs
  LEDStick.LEDOff();
  
  //Color the LEDStick according to the 3 arrays
  LEDStick.setLEDColor(redArray, greenArray, blueArray, 10);
  delay(10);
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
