/*
  An I2C based LED Stick
  By: Ciara Jekel
  SparkFun Electronics
  Date: June 11th, 2018
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

  Feel like supporting our work? Buy a board from SparkFun!
  https://www.sparkfun.com/products/14783

  This example makes a moving rainbow on the LED Stick.

*/

#include "Qwiic_LED_Stick.h" // Click here to get the library: http://librarymanager/All#Sparkfun_Qwiic_LED_Stick

byte redArray[20];
byte greenArray[20];
byte blueArray[20];
LED LEDStick;

void setup() {
  Serial.begin(9600);
  LEDStick.begin();
}
void loop() {
  WalkingRainbow(redArray, greenArray, blueArray, 20, 10, 100);

}

//Walks a rainbow of length RainbowLength across LED strip of length LED Length with a delay of delayTime
//Pass in 3 arrays of length RainbowLength, where RainbowLength<=255
void WalkingRainbow(byte * redArray, byte * greenArray, byte * blueArray, byte RainbowLength, byte LEDLength, int delayTime) {
  for (byte j = 0; j < RainbowLength; j++) {
    for (byte i = 0 ; i < RainbowLength ; i++) {
      float temp;
      int n = i + 1 - j;
      if (n <= 0) n += RainbowLength;
      if (n <= floor(RainbowLength / 6)) {
        redArray[i] = 255;
        greenArray[i] = floor(6 * 255 / (float) RainbowLength * n);
        blueArray[i] = 0;
      }
      else if (n <= floor(RainbowLength / 3)) {
        redArray[i] = floor(510 - 6 * 255 / (float) RainbowLength * n);
        greenArray[i] = 255;
        blueArray[i] = 0;
      }
      else if (n <= floor(RainbowLength / 2)) {
        redArray[i] = 0;
        greenArray[i] = 255;
        blueArray[i] = floor( 6 * 255 / (float) RainbowLength * n - 510);
      }
      else if ( n <= floor(2 * RainbowLength / 3)) {
        redArray[i] = 0;
        greenArray[i] = floor(1020 - 6 * 255 / (float) RainbowLength * n);
        blueArray[i] = 255;
      }
      else if (n <= floor(5 * RainbowLength / 6)) {
        redArray[i] = floor(6 * 255 / (float) RainbowLength * n - 1020);
        greenArray[i] = 0;
        blueArray[i] = 255;
      }
      else {
        redArray[i] = 255;
        greenArray[i] = 0;
        blueArray[i] = floor(1530 - (6 * 255 / (float)RainbowLength * n));;
      }
    }
    LEDStick.setLEDColor(redArray, greenArray, blueArray, LEDLength);
    delay(delayTime);
  }
}

