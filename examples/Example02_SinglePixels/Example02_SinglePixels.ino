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
