/*
  An I2C based LED Stick
  By: Ciara Jekel
  SparkFun Electronics
  Date: June 11th, 2018
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

  Feel like supporting our work? Buy a board from SparkFun!
  https://www.sparkfun.com/products/14783

  This example changes the address of the LED stick and shows the results by writing the whole strip white.
  Address will not reset on restart. Change the address back to defualt with LEDStick.changeAddress(0x29, 0x23);
  Uploading another sketch will require LEDStick.begin(0x29);

*/
#include <Wire.h>
#include "Qwiic_LED_Stick.h" // Click here to get the library: http://librarymanager/All#SparkFun_Qwiic_LED_Stick

LED LEDStick; //Create an object of the LED class

int currentAddress = 0x23;
int newAddress = 0x29;

void setup() {
  Wire.begin();
  Serial.begin(115200);
  
  //Start up communication with the LED Stick
  if (LEDStick.begin(currentAddress) == false){
    Serial.println("Qwiic LED Stick failed to begin. Please check wiring and try again!");
  }

  else {
    Serial.println("Qwiic LED Stick ready!");
    Serial.println();
    
    //Change the address of the LEDStick
    //First, check that the address is valid
    if (newAddress > 0x08 && newAddress < 0x77) {
      Serial.println("Address is valid.");
      Serial.print("Attempting to set the device address to 0x");
      Serial.println(newAddress, HEX);
      Serial.println();
      
      if (LEDStick.changeAddress(newAddress) == true){
        Serial.println("I2C address change successful!");
        Serial.println();
      }
      
      //Set all LEDs dim white.
      //Note that the call for this command doesn't depend on an address
      LEDStick.setLEDColor(10, 10, 10);
    } 
    
    else {
      Serial.println("Address out of range! Try an address between 0x08 and 0x77");
      Serial.println();
    }
    
  }
}

void loop() {
  //if no I2C device found or Qwiic button correctly set to new address, 
  //scan for available I2C devices
  byte error, address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for (address = 1; address < 127; address++ )
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.print(address, HEX);
      Serial.println("  !");

      nDevices++;
    }
    else if (error == 4)
    {
      Serial.print("Unknown error at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");

  delay(5000);           // wait 5 seconds for next scan
}
