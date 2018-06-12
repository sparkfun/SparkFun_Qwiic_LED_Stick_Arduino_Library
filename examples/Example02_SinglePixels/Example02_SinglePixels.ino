/*
  An I2C based LED Stick
  By: Ciara Jekel
  SparkFun Electronics
  Date: June 11th, 2018
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

  Feel like supporting our work? Buy a board from SparkFun!
  https://www.sparkfun.com/products/14783

  This example will alternate blinking two single LEDs on the LED Stick.

*/

#include "Qwiic_LED_Stick.h" // Click here to get the library: http://librarymanager/All#Sparkfun_Qwiic_LED_Stick

LED LEDStick; //Create an object of the LED class

void setup() {
  Serial.begin(9600);
  //Start up communication with the LED Stick
  LEDStick.begin();
}

void loop() {
  //turn off all LEDs
  LEDStick.LEDOff();
  //turn on LED#4, red
  LEDStick.setLEDColor(4, 255, 0, 0);
  delay(1000);
  //turn off all LEDs
  LEDStick.LEDOff();
  //turn on LED#6, red
  LEDStick.setLEDColor(6, 255, 0, 0); 
  delay(1000);

}

