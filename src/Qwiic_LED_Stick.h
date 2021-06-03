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
#define COMMAND_WRITE_ALL_LED_OFF (0x78)

class LED
{
    // user-accessible "public" interface
  public:
	LED();
    //Initialize parameters such as I2C address and port for communication
	boolean begin(uint8_t address = 0x23, TwoWire &wirePort = Wire);//If user doesn't specificy then 0x23 and Wire will be used
	
	//Test I2C connection on I2C address
	boolean isConnected();
	
	//Change the color of a specific LED 
	//each color must be a value between 0-255
	//LEDS indexed starting at 1
    boolean setLEDColor(uint8_t number, uint8_t red, uint8_t green, uint8_t blue);
    
	//Change the color of all LEDs
	//each color must be a value between 0-255
	boolean setLEDColor(uint8_t red, uint8_t green, uint8_t blue);
	
	//Change the color of all LEDs at once to individual values
	//Pass in 3 arrays of color values of length 'length'
	//each color must be a value between 0-255
    boolean setLEDColor(uint8_t redArray[], uint8_t greenArray[], uint8_t blueArray[], uint8_t length);
   
	//Change the brightness of a specific LED, while keeping their current color
	//brightness must be a value between 0-31
	//To turn LEDs off but remember their previous color, set brightness to 0
	//LEDS indexed starting at 1
	boolean setLEDBrightness(uint8_t number, uint8_t brightness);
  
	//Change the brightness of all LEDs, while keeping their current color
	//brightness must be a value between 0-31
	//To turn all LEDs off but remember their previous color, set brightness to 0
	boolean setLEDBrightness(uint8_t brightness);
  
	//Turn all LEDS off by setting color to 0
	boolean LEDOff(void);
  
	//Change the I2C address from one address to another
	boolean changeAddress(uint8_t newAddress);
  
	//Change the length of LEDs
	boolean changeLength(uint8_t newLength);

  private:
	//This stores the current I2C address of the LED Stick
	uint8_t _LEDAddress;
	//This stores the requested i2c port
	TwoWire * _i2cPort;
}; 

#endif
