/*
  An I2C based LED Stick
  By: Ciara Jekel
  SparkFun Electronics
  Date: June 11th, 2018
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

  Feel like supporting our work? Buy a board from SparkFun!
  https://www.sparkfun.com/products/14783

  This example will display a linear gradient from one color to another on the LED Stick.

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

  //Start by resetting the state of the LEDs
  LEDStick.LEDOff();
  
  //Set colors for the gradient
  //These are for the first color
  byte r1 = 238, g1 = 49, b1 = 36;
  //Thses are for the last color
  byte r2 = 66, g2 = 235, b2 = 23;
  //Display the gradient on the LED Stick
  colorGradient(r1, g1, b1, r2, g2, b2, 10);
}

void loop() {

}

//Display a linear gradient from color 1 (r1,g1,b1) to color 2 (r2,g2,b2) on LED strip of length LEDLength
void colorGradient(byte r1, byte g1, byte b1, byte r2, byte g2, byte b2, byte LEDLength) {
  //These will store the slope for a linear equation between
  //r/g/b1 and r/g/b2
  float rSlope, gSlope, bSlope;
  //Subtract 1 from LEDLength because there is one less
  //transition color than length of LEDs
  LEDLength--;
  //Calculate the slope of the line between r/g/b1 and r/g/b2
  rSlope = (r2 - r1) / (float)LEDLength;
  gSlope = (g2 - g1) / (float)LEDLength;
  bSlope = (b2 - b1) / (float)LEDLength;
  //Will repeat for each pixel in your LED Stick
  for (byte i = 0; i <= LEDLength; i++) {
    //Evaluate the ith point on the line between r/g/b1 and r/g/b2
    byte rValue = r1 + rSlope * i;
    byte gValue = g1 + gSlope * i;
    byte bValue = b1 + bSlope * i;
    //Set the (i+1)th pixel to the calculated color
    //the first LED corresponds to the 0th point on the line
    LEDStick.setLEDColor(i, rValue, gValue, bValue);
  }
}
