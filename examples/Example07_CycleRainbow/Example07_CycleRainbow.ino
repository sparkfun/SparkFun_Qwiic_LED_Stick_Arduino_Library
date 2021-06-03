/*
  An I2C based LED Stick
  By: Ciara Jekel
  SparkFun Electronics
  Date: June 11th, 2018
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

  Feel like supporting our work? Buy a board from SparkFun!
  https://www.sparkfun.com/products/14783

  This example makes the LED Stick smoothly change through the colors of the rainbow.

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
  CycleRainbow(10);
}

//Cycle through the rainbow with all LEDs the same color
void CycleRainbow(int delayTime) {
  //will repeat for each color from red to yellow
  for (byte g = 0; g < 255; g++) {
    //Set all LEDs to max red with green increasing each repetition
    LEDStick.setLEDColor(255, g, 0);
    delay(delayTime);
  }
  //will repeat for each color from yellow to green
  for (byte r = 255; r > 0; r--) {
    //Set all LEDs to max green with red decreasing each repetition
    LEDStick.setLEDColor(r, 255, 0);
    delay(delayTime);
  }
  //will repeat for each color from green to cyan
  for (byte b = 0; b < 255; b++) {
    //Set all LEDs to max green with blue increasing each repetition
    LEDStick.setLEDColor(0, 255, b);
    delay(delayTime);
  }
  //will repeat for each color from cyan to blue
  for (byte g = 255; g > 0; g--) {
    //Set all LEDs to max blue with green decreasing each repetition
    LEDStick.setLEDColor(0, g, 255);
    delay(delayTime);
  }
  //will repeat for each color from blue to magenta
  for (byte r = 0; r < 255; r++) {
    //Set all LEDs to max blue with red increasing each repetition
    LEDStick.setLEDColor(r, 0, 255);
    delay(delayTime);
  }
  //will repeat for each color from magenta to red
  for (byte b = 255; b > 0; b--) {
    //Set all LEDs to max red with blue decreasing each repetition
    LEDStick.setLEDColor(255, 0, b);
    delay(delayTime);
  }
}
