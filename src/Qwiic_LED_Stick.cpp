/*
  This is a library written for the Qwiic LED Stick.
  By Ciara Jekel @ SparkFun Electronics, June 11th, 2018

  The Qwiic LED Stick features ten addressable APA102 LEDs, 
  making it easy to add full color LED control using I2C. 
  Write to individual LEDs to display a count in binary,
  or write to the whole strip for cool lighting effects
  
  https://github.com/sparkfun/SparkFun_Qwiic_LED_Stick_Arduino_Library

  Development environment specifics:
  Arduino IDE 1.8.5

  SparkFun labored with love to create this code. Feel like supporting open
  source hardware? Buy a board from SparkFun!
  https://www.sparkfun.com/products/14783
*/


#include "Qwiic_LED_Stick.h"

//Constructor
LED::LED() {
  _LEDAddress = 0;
}

//Start I2C communication
boolean LED::begin(uint8_t address, TwoWire &wirePort) {
  if (address < 0x08 || address > 0x77) return false; //invalid I2C addresses
  _LEDAddress = address; //store the address in a private global variable
  _i2cPort = &wirePort; //Grab which port the user wants us to use		
  
 return isConnected();
}

boolean LED::isConnected() {
  _i2cPort->beginTransmission(_LEDAddress);
  if (_i2cPort->endTransmission() == 0)
    return true;
  return false;
}

//Change the color of a specific LED
//each color must be a value between 0-255
//LEDS indexed starting at 1
boolean LED::setLEDColor(uint8_t number, uint8_t red, uint8_t green, uint8_t blue) {
  // First, boundary check
  if (red > 255)
    red = 255;
  if (red < 0)
    red = 0;
  if (green > 255)
    green = 255;
  if (green < 0)
    green = 0;
  if (blue > 255)
    blue = 255;
  if (blue < 0)
    blue = 0;
  
  _i2cPort->beginTransmission(_LEDAddress); //communicate using address
  _i2cPort->write(COMMAND_WRITE_SINGLE_LED_COLOR); //command to change single LED's color
  _i2cPort->write(number); //choose which LED
  _i2cPort->write(red); //update red value
  _i2cPort->write(green); //update green value
  _i2cPort->write(blue); //update blue value
  if (_i2cPort->endTransmission() != 0)
  {
    //Sensor did not ACK
    return (false);
  }
  return (true);
}
//Change the color of all LEDs
//each color must be a value between 0-255
boolean LED::setLEDColor(uint8_t red, uint8_t green, uint8_t blue) {
  // First, boundary check
  if (red > 255)
    red = 255;
  if (red < 0)
    red = 0;
  if (green > 255)
    green = 255;
  if (green < 0)
    green = 0;
  if (blue > 255)
    blue = 255;
  if (blue < 0)
    blue = 0;

  _i2cPort->beginTransmission(_LEDAddress); //communicate using address
  _i2cPort->write(COMMAND_WRITE_ALL_LED_COLOR); //command to change all LEDs' colors
  _i2cPort->write(red); //update red value
  _i2cPort->write(green); //update green value
  _i2cPort->write(blue); //update blue value
  if (_i2cPort->endTransmission() != 0)
  {
    //Sensor did not ACK
    return (false);
  }
  return (true);
}
//Change the color of all LEDs at once to individual values
//Pass in 3 arrays of color values
//each color must be a value between 0-255
boolean LED::setLEDColor(uint8_t redArray[], uint8_t greenArray[], uint8_t blueArray[], uint8_t length) {
  // First, boundary check
  for (int i = 0; i < length; i++){
    if (redArray[i] > 255)
      redArray[i] = 255;
    if (redArray[i] < 0)
      redArray[i] = 0;
    if (greenArray[i] > 255)
      greenArray[i] = 255;
    if (greenArray[i] < 0)
      greenArray[i] = 0;
    if (blueArray[i] > 255)
      blueArray[i] = 255;
    if (blueArray[i] < 0)
      blueArray[i] = 0;
  }

   //ATtiny has a 16 uint8_t limit on a single I2C transmission,
   //so multiple calls to commands are required
  uint8_t n;
  uint8_t len = length % 12; //value for remainder of division length/12
  for (n = 0; n < length / 12; n++) { //will repeat for the # of times 12 goes into length evenly
    _i2cPort->beginTransmission(_LEDAddress); //communicate using address
    _i2cPort->write(COMMAND_WRITE_RED_ARRAY); //command to change red value of LEDs
    _i2cPort->write(12); //length of expected transmission
    _i2cPort->write(n * 12 ); //write offset
    _i2cPort->write(&redArray[n * 12], 12); //transmit 12 values of color array starting at (n*12)th value
    if (_i2cPort->endTransmission() != 0)
    {
      //Sensor did not ACK
      return false;
    }
  }
  if (len != 0) { //will transmit if there is a remainder of the division length/12
    _i2cPort->beginTransmission(_LEDAddress); //communicate using address
    _i2cPort->write(COMMAND_WRITE_RED_ARRAY); //command to change red value of LEDs
    _i2cPort->write(len); //length of expected transmission is the remainder of the division length/12
    _i2cPort->write(n * 12); //offset
    _i2cPort->write(&redArray[n * 12], len); //transmit len values of color array starting at (n*12)th value
    if (_i2cPort->endTransmission() != 0) {
      //Sensor did not ACK
      return false;
    }
  }
  for (n = 0; n < length / 12; n++) {
    _i2cPort->beginTransmission(_LEDAddress);
    _i2cPort->write(COMMAND_WRITE_GREEN_ARRAY);
    _i2cPort->write(12);
    _i2cPort->write(n * 12 ); //offset
    _i2cPort->write(&greenArray[n * 12], 12);
    if (_i2cPort->endTransmission() != 0)
    {
      //Sensor did not ACK
      return false;
    }
  }
  if (len != 0) {
    _i2cPort->beginTransmission(_LEDAddress);
    _i2cPort->write(COMMAND_WRITE_GREEN_ARRAY);
    _i2cPort->write(len);
    _i2cPort->write(n * 12); //offset
    _i2cPort->write(&greenArray[n * 12], len);
    if (_i2cPort->endTransmission() != 0) {
      //Sensor did not ACK
      return false;
    }
  }
  for (n = 0; n < length / 12; n++) {
    _i2cPort->beginTransmission(_LEDAddress);
    _i2cPort->write(COMMAND_WRITE_BLUE_ARRAY);
    _i2cPort->write(12);
    _i2cPort->write(n * 12 ); //offset
    _i2cPort->write(&blueArray[n * 12], 12);
    if (_i2cPort->endTransmission() != 0)
    {
      //Sensor did not ACK
      return false;
    }
  }
  if (len != 0) {
    _i2cPort->beginTransmission(_LEDAddress);
    _i2cPort->write(COMMAND_WRITE_BLUE_ARRAY);
    _i2cPort->write(len);
    _i2cPort->write(n * 12); //offset
    _i2cPort->write(&blueArray[n * 12], len);
    if (_i2cPort->endTransmission() != 0) {
      //Sensor did not ACK
      return false;
    }
  }
  return (true);
}

//Change the brightness of a specific LED, while keeping their current color
//brightness must be a value between 0-31
//To turn LEDs off but remember their previous color, set brightness to 0
//LEDS indexed starting at 1
boolean LED::setLEDBrightness(uint8_t number, uint8_t brightness) {
  // First, boundary check
  if (brightness > 31)
    brightness = 31;
  if (brightness < 0)
    brightness = 0;

  _i2cPort->beginTransmission(_LEDAddress); //Communicate using the address
  _i2cPort->write(COMMAND_WRITE_SINGLE_LED_BRIGHTNESS); //Command to write single brightness
  _i2cPort->write(number); //Choose which LED
  _i2cPort->write(brightness); //Update brightness 
  if (_i2cPort->endTransmission() != 0)
  {
    //Sensor did not ACK
    return (false);
  }
  return (true);
}

//Change the brightness of all LEDs, while keeping their current color
//brightness must be a value between 0-31
//To turn all LEDs off but remember their previous color, set brightness to 0
boolean LED::setLEDBrightness(uint8_t brightness) {
  // First, boundary check
  if (brightness > 31)
    brightness = 31;
  if (brightness < 0)
    brightness = 0;

  _i2cPort->beginTransmission(_LEDAddress); //Communicate using the address
  _i2cPort->write(COMMAND_WRITE_ALL_LED_BRIGHTNESS); //Commaand to change all brightness
  _i2cPort->write(brightness); //Update brightness
  if (_i2cPort->endTransmission() != 0)
  {
    //Sensor did not ACK
    return (false);
  }
  return (true);
}

//Turn all LEDS off by setting color to 0
boolean LED::LEDOff(void) {
  _i2cPort->beginTransmission(_LEDAddress); //Communicate using the address
  _i2cPort->write(COMMAND_WRITE_ALL_LED_OFF); //Command to turn off
  if (_i2cPort->endTransmission() != 0)
  {
    //Sensor did not ACK
    return (false);
  }
  return (true);
}

//Change the I2C address from one address to another
boolean LED::changeAddress(uint8_t newAddress)
{
  _i2cPort->beginTransmission(_LEDAddress); //Communicate using the old address
  _i2cPort->write(COMMAND_CHANGE_ADDRESS); //0xC7 is the register location on the KeyPad to change its I2C address
  _i2cPort->write(newAddress); //Go to the new address
  if (_i2cPort->endTransmission() != 0)
  {
    //Sensor did not ACK
    return (false);
  }
    _LEDAddress = newAddress;
	return (true);
}
//Change the length of LEDs
boolean LED::changeLength(uint8_t newLength)
{
  _i2cPort->beginTransmission(_LEDAddress); //Communicate using address
  _i2cPort->write(COMMAND_CHANGE_LED_LENGTH); //Command to change the length
  _i2cPort->write(newLength); //Update the length
  if (_i2cPort->endTransmission() != 0)
  {
    //Sensor did not ACK
    return (false);
  }
  return (true);
}
