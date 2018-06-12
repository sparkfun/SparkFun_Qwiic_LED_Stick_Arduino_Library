/*
  An I2C based LED Stick
  By: Ciara Jekel
  SparkFun Electronics
  Date: June 11th, 2018
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

  Feel like supporting our work? Buy a board from SparkFun!
  https://www.sparkfun.com/products/14783

  This example changes the address of the LED stick and shows the results by writing the whole strip white.
  Address will not reset on restart. Change the address back to defualt with LEDStick.changeAddress(0x29, 0x23);
  Uploading another sketch will require LEDStick.begin(0x29);

*/

#include "Qwiic_LED_Stick.h" // Click here to get the library: http://librarymanager/All#Sparkfun_Qwiic_LED_Stick

LED LEDStick; //Create an object of the LED class

void setup() {
  Serial.begin(9600);
  //Start up communication with the LED Stick
  LEDStick.begin();
  //Change the address of the LEDStick from 0x23 to 0x29
  LEDStick.changeAddress(0x23, 0x29);
  //Set all LEDs dim white.
  //Note that the call for this command doesn't depend on an address
  LEDStick.setLEDColor(10, 10, 10);

}

void loop() {


}

