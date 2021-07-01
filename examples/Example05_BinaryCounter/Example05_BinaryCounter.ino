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
}

void loop() {
  //This for loop counts from 0 to 1023
  //and displays the binary on the Serial Monitor
  //and the LED Stick
  for (int i = 0; i < 1024; i++) {
    binaryLEDDisplay(i, 10);
    binarySerialDisplay(i, 10);
    delay(1000);
  }

}

//Display binary on LEDS (LSB==LED10) of length LEDLength
void binaryLEDDisplay(int count, byte LEDLength) {
  byte redArray[LEDLength];
  byte greenArray[LEDLength];
  byte blueArray[LEDLength];
  
  //This for loop will repeat for each pixel of the LED Stick
  for (byte i = 0; i < LEDLength; i++) {
    //Below we use bit operators, which operate on the binary
    //representation of numbers.
    //For ithBit, we use the bitshift operator. count >> i takes the binary
    //representation of count and shifts it to the right i times. For example,
    //if count was 10, 0b1010, and i was 2, we get 0b10. if i was 3, we get 0b1.
    //This aligns the ith bit of count to the 0th bit of ithBit
    byte ithBit = count >> i;
    //Here we use the bitwise and. This returns a 1 only in the places where both
    //operands have a 1. For example, 0b1011 & 0b1010 == 0b1010. Here we use 0b1 as
    //an operand, which means our output will be whatever the 0th bit of ithBit is
    byte ithBitTrue = ithBit & 0b1;
    //Here we write to a single LED. We write only the color red,
    //but you can write to any combination of colors. We write to the
    //(10-i)th LED so that the last LED of your strip maps to bit 0
    //and is the least significant bit, or the one's place. The value
    //for the color will be 255*ithBitTrue. Since ithBitTrue can only
    //be 1 or 0, we only send color values of either 255 or zero. This
    //means that the (10-i)th LED will be red if the ith bit of the
    //count is 1, and will be off otherwise
    redArray[LEDLength - i - 1] = 255 * ithBitTrue;
    greenArray[i] = 0;
    blueArray[i] = 0;
  }
  LEDStick.setLEDColor(redArray, greenArray, blueArray, 10);
}

//Serial.print decimal and binary value of count, expecting lengthBit bits
void binarySerialDisplay(int count, byte lengthBits) {
  Serial.print(count);
  Serial.print("\t|\t");
  //this will repeat lengthBit times
  for (byte i = lengthBits; i > 0 ; i--) { //Start printing at MSB
    //This is the same strategy as above, but here i will always be 1 greater
    //than the bit # so we must subtract 1
    byte ithBit = count >> i-1 ;
    //ithBitTrue will be the value of the 0th bit of ithBit
    byte ithBitTrue = ithBit & 0b1;
    Serial.print(ithBitTrue);
  }
  Serial.print("\n"); //new line
}
