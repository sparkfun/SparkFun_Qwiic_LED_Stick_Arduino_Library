/*
  An I2C based LED Stick
  By: Ciara Jekel
  SparkFun Electronics
  Date: June 11th, 2018
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

  Feel like supporting our work? Buy a board from SparkFun!
  https://www.sparkfun.com/products/14783



*/
#include <Wire.h>
#include "Qwiic_LED_Stick.h" // Click here to get the library: http://librarymanager/All#SparkFun_Qwiic_LED_Stick

LED LEDStick; //Create an object of the LED class

void setup() {
  Wire.begin();
  Serial.begin(9600);
  //Start up communication with the LED Stick at address 0x29 
  LEDStick.begin(0x29);
  LEDStick.setLEDColor(10, 10, 10);

}

void loop() {


}

