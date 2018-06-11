/*
  An I2C based LED Stick
  By: Ciara Jekel
  SparkFun Electronics
  Date: June 11th, 2018
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

  Feel like supporting our work? Buy a board from SparkFun!
  https://www.sparkfun.com/products/14783

  This example counts up from 0 to 1023 and displays
  the number in binary on the LED Stick.

*/

#include "Qwiic_LED_Stick.h" // Click here to get the library: http://librarymanager/All#Sparkfun_Qwiic_LED_Stick

LED LEDStick;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  LEDStick.begin();
}

void loop() {
  for (int i = 0; i < 1024; i++) {
    binaryLEDDisplay(i, 10);
    binarySerialDisplay(i,10);
    delay(1000);
  }

}

//Display binary on LEDS (LSB==LED10) of length LEDLength
void binaryLEDDisplay(int count, byte LEDLength) {
  for (byte i = 0; i < LEDLength; i++) {
    //(10-i)th LED will be red if the ith bit of the count is not zero
    LEDStick.setLEDColor(10-i, 255 * ((count & 1 << i) != 0), 0, 0); 
  }
}

//Serial.print decimal and binary value of count, expecting n bits
void binarySerialDisplay(int count, byte n) {
  Serial.print(count);
  Serial.print("\t|\t");
  for (byte i = n; i > 0 ; i--) { //Start printing at MSB
    //ith bit will be 1 if the ith bit of the count is not zero, and 0 if it is 0
    Serial.print((count & 1 << (i - 1)) != 0);  
  }
  Serial.print("\n"); //new line
}

