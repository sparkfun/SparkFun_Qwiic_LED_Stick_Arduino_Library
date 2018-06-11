/*
  This is a library written for the Qwiic LED Stick.
  By Ciara Jekel @ SparkFun Electronics, June 11th, 2018

  The Qwiic LED Stick features ten addressable APA102 LEDs,
  making it easy to add an output to your latest project.
  Write to individual LEDs to display a count in binary,
  or write to the whole strip for cool lighting effects
  
  https://github.com/sparkfun/SparkFun_Qwiic_LED_Stick_Arduino_Library

  Development environment specifics:
  Arduino IDE 1.8.5

  SparkFun labored with love to create this code. Feel like supporting open
  source hardware? Buy a board from SparkFun!
  https://www.sparkfun.com/products/14783
*/

#ifndef Qwiic_LED_Stick_h
#define Qwiic_LED_Stick_h

#include "Arduino.h"
#include <Wire.h>

#define COMMAND_CHANGE_ADDRESS (0xC7)
#define COMMAND_CHANGE_LED_LENGTH (0x70)
#define COMMAND_WRITE_SINGLE_LED_COLOR (0x71)
#define COMMAND_WRITE_ALL_LED_COLOR (0x72)
#define COMMAND_WRITE_RED_ARRAY (0x73)
#define COMMAND_WRITE_GREEN_ARRAY (0x74)
#define COMMAND_WRITE_BLUE_ARRAY (0x75)
#define COMMAND_WRITE_SINGLE_LED_BRIGHTNESS (0x76)
#define COMMAND_WRITE_ALL_LED_BRIGHTNESS (0x77)
#define COMMAND_WRITE_ALL_LED_UNIQUE_BRIGHTNESS (0x78)
#define COMMAND_WRITE_ALL_LED_OFF (0x79)

class LED
{
    // user-accessible "public" interface
  public:
    LED();
    boolean begin(byte address = 0x23);
    boolean setLEDColor(byte number, byte red, byte green, byte blue);
    boolean setLEDColor(byte red, byte green, byte blue);
    boolean setLEDColor(byte redArray[], byte greenArray[], byte blueArray[], byte length);
    boolean setLEDBrightness(byte number, byte brightness);
    boolean setLEDBrightness(byte brightness);
    boolean LEDOff(void);
    boolean changeAddress(byte oldAddress, byte newAddress);
    boolean changeLength(byte newLength);

  private:
    byte _LEDAddress;
};

#endif
