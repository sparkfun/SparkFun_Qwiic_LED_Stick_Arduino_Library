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

#include <Wire.h>
#include "Qwiic_LED_Stick.h" // Click here to get the library: http://librarymanager/All#SparkFun_Qwiic_LED_Stick


//Create an object of the LED class
LED LEDStick;

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
  WalkingRainbow(20, 10, 100);
}

//Walks a rainbow of length rainbowLength across LED strip of length LED Length with a delay of delayTime
//LEDLength<=rainbowLength<=255)
void WalkingRainbow(byte rainbowLength, byte LEDLength, int delayTime) {
  //Create three LEDs the same length as the LEDStick to store color values
  byte redArray[LEDLength];
  byte greenArray[LEDLength];
  byte blueArray[LEDLength];
  //This will repeat rainbowLength times, generating 3 arrays (r,g,b) of length LEDLength
  //This is like creating rainbowLength differnent rainbow arrays where the positions
  //of each color have changed by 1
  for (byte j = 0; j < rainbowLength; j++) {
    //This will repeat LEDLength times, generating 3 colors (r,g,b) per pixel
    //This creates the array that is sent to the LED Stick
    for (byte i = 0 ; i < LEDLength ; i++) {
      //there are n colors generated for the rainbow
      //the rainbow starts at the location where i and j are equal: n=1
      //the +1 accounts for the LEDs starting their index at 0
      //the value of n determines which color is generated at each pixel
      int n = i + 1 - j;
      //this will loop n so that n is always between 1 and rainbowLength
      if (n <= 0) {
        n = n + rainbowLength; 
      }
      //the nth color is between red and yellow
      if (n <= floor(rainbowLength / 6)) {
        redArray[i] = 255;
        greenArray[i] = floor(6 * 255 / (float) rainbowLength * n);
        blueArray[i] = 0;
      }
      //the nth color is between yellow and green
      else if (n <= floor(rainbowLength / 3)) {
        redArray[i] = floor(510 - 6 * 255 / (float) rainbowLength * n);
        greenArray[i] = 255;
        blueArray[i] = 0;
      }
      //the nth color is between green and cyan
      else if (n <= floor(rainbowLength / 2)) {
        redArray[i] = 0;
        greenArray[i] = 255;
        blueArray[i] = floor( 6 * 255 / (float) rainbowLength * n - 510);
      }
      //the nth color is between cyan and blue
      else if ( n <= floor(2 * rainbowLength / 3)) {
        redArray[i] = 0;
        greenArray[i] = floor(1020 - 6 * 255 / (float) rainbowLength * n);
        blueArray[i] = 255;
      }
      //the nth color is between blue and magenta
      else if (n <= floor(5 * rainbowLength / 6)) {
        redArray[i] = floor(6 * 255 / (float) rainbowLength * n - 1020);
        greenArray[i] = 0;
        blueArray[i] = 255;
      }
      //the nth color is between magenta and red
      else {
        redArray[i] = 255;
        greenArray[i] = 0;
        blueArray[i] = floor(1530 - (6 * 255 / (float)rainbowLength * n));;
      }
    }
    //sets all LEDs to the color values according to the arrays
    //the first LED corresponds to the first entries in the arrays
    LEDStick.setLEDColor(redArray, greenArray, blueArray, LEDLength);
    delay(delayTime);
  }
}
