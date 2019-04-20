#include "LP5036.h"


LP5036::LP5036(){
  }


  void LP5036::reset() // return to default registers/conditions
{
  writeByte(LP5036_ADDRESS, LP5036_RESET, 0xFF);
}


  void LP5036::powerDown()
  {
  writeByte(LP5036_ADDRESS, LP5036_DEVICE_CONFIG0, 0x00); //clear bit 6 to shut down
  }


  void LP5036::powerUp()
  {
  writeByte(LP5036_ADDRESS, LP5036_DEVICE_CONFIG0, 0x40); //set bit 6 to enable
  }


  void LP5036::init()
 {

  // Bit 5 linear (0) or log scale (1)
  // Bit 4 autopower save not enabled (0) or enabled(1)
  // Bit 3 autoincrement not enabled (0) or enabled (1)
  // Bit 2 PWM dithering not enabled (0) or enabled (1)
  // Bit 1 Output max current 25.5 mA (0) or 35 mA (1)
  //  
  writeByte(LP5036_ADDRESS,LP5036_DEVICE_CONFIG1,0x20 | 0x10 | 0x08 | 0x04);
 }


void LP5036::bankControlOn()
{
  writeByte(LP5036_ADDRESS,LP5036_LED_CONFIG0,0xFF);
  writeByte(LP5036_ADDRESS,LP5036_LED_CONFIG1,0x0F);
}


void LP5036::bankControlOff()
{
  writeByte(LP5036_ADDRESS,LP5036_LED_CONFIG0,0x00);
  writeByte(LP5036_ADDRESS,LP5036_LED_CONFIG1,0x00);
}


void LP5036::bankBrightness(uint8_t brightness)
{
  writeByte(LP5036_ADDRESS,LP5036_BANK_BRIGHTNESS,brightness);
}


void LP5036::bankColor(uint8_t red, uint8_t green, uint8_t blue)
{
  writeByte(LP5036_ADDRESS,LP5036_BANK_A_COLOR,red);
  writeByte(LP5036_ADDRESS,LP5036_BANK_B_COLOR,green);
  writeByte(LP5036_ADDRESS,LP5036_BANK_C_COLOR,blue);
}


  void LP5036::setBrightness(uint8_t channel, uint8_t brightness)
 {
  writeByte(LP5036_ADDRESS, LP5036_LED0_BRIGHTNESS + channel, brightness); // set led brightness
 }


 void LP5036::setColor(uint8_t channel, uint8_t color)
 {
  writeByte(LP5036_ADDRESS, LP5036_OUT0_COLOR + channel, color);  // set color level (0 - 255) for specified led channel
 }


 void LP5036::setRunMode()
 {
  uint8_t temp = readByte(LP5036_ADDRESS,LP5036_DEVICE_CONFIG1);
  writeByte(LP5036_ADDRESS,LP5036_DEVICE_CONFIG1, temp | ~(0x01) ); // normal operation 
 }


 void LP5036::setStopMode()
 {
  uint8_t temp = readByte(LP5036_ADDRESS,LP5036_DEVICE_CONFIG1);
  writeByte(LP5036_ADDRESS,LP5036_DEVICE_CONFIG1, temp | 0x01 ); // shut down all leds 
  }


// I2C scan function
void LP5036::I2Cscan()
{
// scan for i2c devices
  byte error, address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for(address = 1; address < 127; address++ ) 
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmission to see if
    // a device did acknowledge to the address.
//    Wire.beginTransmission(address);
//    error = Wire.endTransmission();
      error = Wire.transfer(address, NULL, 0, NULL, 0);
      
    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16) 
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");

      nDevices++;
    }
    else if (error==4) 
    {
      Serial.print("Unknown error at address 0x");
      if (address<16) 
        Serial.print("0");
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");  
}


// I2C read/write functions  

   void LP5036::writeByte(uint8_t address, uint8_t subAddress, uint8_t data) {
   Wire.beginTransmission(address); // starts transaction
   Wire.write(subAddress); // sends register address
   Wire.write(data      ); // sends data
   Wire.endTransmission(); // stop transmitting
   }

   uint8_t LP5036::readByte(uint8_t address, uint8_t subAddress)
{
   uint8_t data = 0;                        // `data` will store the register data   
   Wire.beginTransmission(address);         // Initialize the Tx buffer
   Wire.write(subAddress);                  // Put slave register address in Tx buffer
   Wire.endTransmission(false);             // Send the Tx buffer, but send a restart to keep connection alive
   Wire.requestFrom(address, 1);            // Read one byte from slave register address  
   data = Wire.read();                      // Fill Rx buffer with result
   return data;                             // Return data read from slave register
}
