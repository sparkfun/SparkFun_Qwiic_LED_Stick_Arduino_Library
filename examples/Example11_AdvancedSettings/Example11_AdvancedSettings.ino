/*
  An I2C based LED Stick
  By: Ciara Jekel
  SparkFun Electronics
  Date: June 11th, 2018
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

  Feel like supporting our work? Buy a board from SparkFun!
  https://www.sparkfun.com/products/14783

  This example shows how to use two LED Sticks on the same I2C bus
*/
#include <Wire.h>
#include "Qwiic_LED_Stick.h" // Click here to get the library: http://librarymanager/All#SparkFun_Qwiic_LED_Stick

LED LEDStick1; //Create an object of the LED class
LED LEDStick2; //Create an object of the LED class


void setup() {
  Wire.begin();
  Serial.begin(115200);
  
  //Start up communication with the LED Stick 1
  if (LEDStick1.begin() == false){
    Serial.println("Qwiic LED Stick 1 failed to begin. Please check wiring and try again!");
    while(1);
  }
  
  Serial.println("Qwiic LED Stick 1 ready!");
  //Set the whole 1st LED Stick dim white
  LEDStick1.setLEDColor(10, 10, 10);
  
  //Start up communication with another LED Stick 2 at address 0x29
  if (LEDStick2.begin(0x29) == false){
    Serial.println("Qwiic LED Stick 2 failed to begin. Please check wiring and try again!");
    while(1);
  }

  Serial.println("Qwiic LED Stick 2 ready!");

  //Set the whole 2nd LED Stick dim white
  LEDStick2.setLEDColor(10, 10, 10);


}

void loop() {


}
