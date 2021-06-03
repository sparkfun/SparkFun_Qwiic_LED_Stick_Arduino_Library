/*
  An I2C based LED Stick
  By: Ciara Jekel
  SparkFun Electronics
  Date: June 11th, 2018
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

  Feel like supporting our work? Buy a board from SparkFun!
  https://www.sparkfun.com/products/14783

  This example changes each LED of the LED Stick to an arbitrary color.

*/

#include <Wire.h>
#include "Qwiic_LED_Stick.h" // Click here to get the library: http://librarymanager/All#SparkFun_Qwiic_LED_Stick

LED LEDStick; //Create an object of the LED class
//Create 3 arrays the same length as the LED stick,
//Initializing them with arbitrary values
//           Pixel#     1    2    3    4    5    6    7    8    9   10
byte redArray[10]   = {214,  78, 183, 198,  59, 134,  15, 209, 219, 186}; //r
byte greenArray[10] = { 59, 216, 170,  21, 114,  63, 226,  92, 155, 175}; //g
byte blueArray[10]  = {214, 147,  25, 124, 153, 163, 188,  33, 175, 221}; //b

void setup() {
  Wire.begin();
  Serial.begin(115200);
  
  //Start up communication with the LED Stick
  if (LEDStick.begin() == false){
    Serial.println("Qwiic LED Stick failed to begin. Please check wiring and try again!");
    while(1);
  }

  Serial.println("Qwiic LED Stick ready!");
  
  //Set all pixels at once to the color values
  //corresponding to same the entry in the array
  //e.g. the third LED will be the color of the
  //r,g,b values from the third entries in the array
  LEDStick.setLEDColor(redArray, greenArray, blueArray, 10);
}


void loop() {

}
