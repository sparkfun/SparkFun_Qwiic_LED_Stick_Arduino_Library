/*
  An I2C based LED Stick
  By: Ciara Jekel
  SparkFun Electronics
  Date: June 11th, 2018
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

  Feel like supporting our work? Buy a board from SparkFun!
  https://www.sparkfun.com/products/14783

  This example changes the length of the attached LED strip and shows the results by writing the whole strip white.
  Length will not reset on restart, change back to 10 if necessary with LEDStick.changeLength(10);
  If you add LEDs to the end of the stick, you must change the length to be able to use them.
  
*/

#include <Wire.h>
#include "Qwiic_LED_Stick.h" // Click here to get the library: http://librarymanager/All#SparkFun_Qwiic_LED_Stick

LED LEDStick; //Create an object of the LED class

void setup() {
  Wire.begin();
  Serial.begin(115200);
  
  //Start up communication with the LED Stick
  if (LEDStick.begin() == false){
    Serial.println("Qwiic LED Stick failed to begin. Please check wiring and try again!");
    while(1);
  }

  Serial.println("Qwiic LED Stick ready!");

  //First, turn all LEDs off
  LEDStick.LEDOff();
  delay(500); //Wait for settings to be updated
  
  //Change LED length to 5
  //This will allow you to write to a maximum of 5 LEDs
  LEDStick.changeLength(5);
  //Set all LEDs dim white, notice only 5 are lit.
  LEDStick.setLEDColor(10, 10, 10);
}

void loop() {


}
