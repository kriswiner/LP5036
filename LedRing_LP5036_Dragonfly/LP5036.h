/* 04/20/2019 Copyright Tlera Corporation
 *  
 *  Created by Kris Winer
 *  
 This sketch uses SDA/SCL ons the Dragonfly STM32L476RE Breakout Board.
 The LP5036 is a simple led driver capable of driving 12 rgb leds or 36 single leds.
 
 Library may be used freely and without limit with attribution.
 
*/
  
#ifndef LP5036_h
#define LP5036_h

#include "Arduino.h"
#include <Wire.h>

/* LP5036 registers
*  http://www.ti.com/lit/ds/symlink/lp5036.pdf
*/
#define LP5036_DEVICE_CONFIG0    0x00
#define LP5036_DEVICE_CONFIG1    0x01
#define LP5036_LED_CONFIG0       0x02
#define LP5036_LED_CONFIG1       0x03
#define LP5036_BANK_BRIGHTNESS   0x04
#define LP5036_BANK_A_COLOR      0x05
#define LP5036_BANK_B_COLOR      0x06
#define LP5036_BANK_C_COLOR      0x07
#define LP5036_LED0_BRIGHTNESS   0x08
#define LP5036_LED1_BRIGHTNESS   0x09
#define LP5036_LED2_BRIGHTNESS   0x0a
#define LP5036_LED3_BRIGHTNESS   0x0b
#define LP5036_LED4_BRIGHTNESS   0x0c
#define LP5036_LED5_BRIGHTNESS   0x0d
#define LP5036_LED6_BRIGHTNESS   0x0e
#define LP5036_LED7_BRIGHTNESS   0x0f
#define LP5036_LED8_BRIGHTNESS   0x10
#define LP5036_LED9_BRIGHTNESS   0x11
#define LP5036_LED10_BRIGHTNESS  0x12
#define LP5036_LED11_BRIGHTNESS  0x13

#define LP5036_OUT0_COLOR   0x14
#define LP5036_OUT1_COLOR   0x15
#define LP5036_OUT2_COLOR   0x16
#define LP5036_OUT3_COLOR   0x17
#define LP5036_OUT4_COLOR   0x18
#define LP5036_OUT5_COLOR   0x19
#define LP5036_OUT6_COLOR   0x1a
#define LP5036_OUT7_COLOR   0x1b
#define LP5036_OUT8_COLOR   0x1c
#define LP5036_OUT9_COLOR   0x1d
#define LP5036_OUT10_COLOR  0x1e
#define LP5036_OUT11_COLOR  0x1f
#define LP5036_OUT12_COLOR  0x20
#define LP5036_OUT13_COLOR  0x21
#define LP5036_OUT14_COLOR  0x22
#define LP5036_OUT15_COLOR  0x23
#define LP5036_OUT16_COLOR  0x24
#define LP5036_OUT17_COLOR  0x25
#define LP5036_OUT18_COLOR  0x26
#define LP5036_OUT19_COLOR  0x27
#define LP5036_OUT20_COLOR  0x28
#define LP5036_OUT21_COLOR  0x29
#define LP5036_OUT22_COLOR  0x2a
#define LP5036_OUT23_COLOR  0x2b
#define LP5036_OUT24_COLOR  0x2c
#define LP5036_OUT25_COLOR  0x2d
#define LP5036_OUT26_COLOR  0x2e
#define LP5036_OUT27_COLOR  0x2f
#define LP5036_OUT28_COLOR  0x30
#define LP5036_OUT29_COLOR  0x31
#define LP5036_OUT30_COLOR  0x32
#define LP5036_OUT31_COLOR  0x33
#define LP5036_OUT32_COLOR  0x34
#define LP5036_OUT33_COLOR  0x35
#define LP5036_OUT34_COLOR  0x36
#define LP5036_OUT35_COLOR  0x37
#define LP5036_RESET        0x38

#define LP5036_ADDRESS 0x1C // when AD0 = AD1 = LOW (default)


class LP5036
{
  public: 
  LP5036();
  void reset();
  void powerDown();
  void powerUp();
  void init();
  void setBrightness(uint8_t channel, uint8_t brightness);
  void setColor(uint8_t channel, uint8_t color);
  void setRunMode();
  void setStopMode();
  void bankControlOn();
  void bankControlOff();
  void bankBrightness(uint8_t brightness);
  void bankColor(uint8_t red, uint8_t green, uint8_t blue);
  void I2Cscan();
  void writeByte(uint8_t address, uint8_t subAddress, uint8_t data);
  uint8_t readByte(uint8_t address, uint8_t subAddress);
  private:

 };

#endif
