/* 
 * 02/23/2019 Copyright Tlera Corporation
 *  
 *  Created by Kris Winer
 *  
 *  The LP5036 is a 12-channel rgb led controller (http://www.ti.com/lit/ds/symlink/lp5036.pdf).
 *  
 *  This sketch uses default SDA/SCL pins on the Dragonfly/Butterfly development boards
 *
 *  Library may be used freely and without limit with attribution.
 */
#include "LP5036.h"

#include <avr/pgmspace.h>

byte PWM_Gamma64[64]=
{
  0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,
  0x08,0x09,0x0b,0x0d,0x0f,0x11,0x13,0x16,
  0x1a,0x1c,0x1d,0x1f,0x22,0x25,0x28,0x2e,
  0x34,0x38,0x3c,0x40,0x44,0x48,0x4b,0x4f,
  0x55,0x5a,0x5f,0x64,0x69,0x6d,0x72,0x77,
  0x7d,0x80,0x88,0x8d,0x94,0x9a,0xa0,0xa7,
  0xac,0xb0,0xb9,0xbf,0xc6,0xcb,0xcf,0xd6,
  0xe1,0xe9,0xed,0xf1,0xf6,0xfa,0xfe,0xff
};

const boolean invert = false; // set true if common anode, false if common cathode

uint8_t color = 0;        // a value from 0 to 255 representing the hue
uint8_t R, G, B;          // the Red Green and Blue color components
uint8_t brightness = 255; // 255 is maximum brightness

LP5036 LP5036; // instantiate LP5036 class

void setup() {
  Serial.begin(115200);
  delay(4000);
  
  Wire.begin(TWI_PINS_20_21); // set master mode 
  Wire.setClock(400000); // I2C frequency at 400 kHz  
  delay(1000);
 
  LP5036.I2Cscan();

  LP5036.powerUp();

  LP5036.init(); // set PWM frequency and output current for all leds

} /* end of Setup */

void loop() {

  LP5036.setRunMode();
  LP5036.bankControlOff(); // control each rgb led individually to test function
  
  // Turn on leds slowly from 1 to 12 one at a time at 1/4 intensity
  for(uint8_t ii = 0x00; ii <=0x0B; ii++)
  {
    LP5036.setBrightness(ii, 0x30);  // 64/256
    LP5036.setColor(ii*3,   0xFF); // red only
    LP5036.setColor(ii*3+1, 0x00);
    LP5036.setColor(ii*3+2, 0x00);
    delay(100);
  }
  delay(1000);

  
  // Turn off leds slowly from 1 to 12 one at a time  
  for(uint8_t ii = 0x00; ii <=0x0B; ii++)
  {
    LP5036.setBrightness(ii, 0x30);
    LP5036.setColor(ii*3,   0x00);
    LP5036.setColor(ii*3+1, 0x00);
    LP5036.setColor(ii*3+2, 0x00);
    delay(100);
  }
  delay(1000);

  // Turn on leds quickly from 1 to 12 one at a time at 1/2 intensity
    for(uint8_t ii = 0x00; ii <=0x0B; ii++)
  {
    LP5036.setBrightness(ii, 0x80); // 128/256
    LP5036.setColor(ii*3,   0x00);
    LP5036.setColor(ii*3+1, 0xFF); // green only
    LP5036.setColor(ii*3+2, 0x00);
    delay(50);
  }
  delay(1000);
  
  // Turn off leds quickly from 1 to 36 one at a time  
  for(uint8_t ii = 0x00; ii <=0x0B; ii++)
  {
    LP5036.setBrightness(ii, 0x80);
    LP5036.setColor(ii*3,   0x00);
    LP5036.setColor(ii*3+1, 0x00);
    LP5036.setColor(ii*3+2, 0x00);
    delay(50);
  }
  delay(1000);

    // Turn on leds very quickly from 1 to 12 one at a time at full intensity
    for(uint8_t ii = 0x00; ii <=0x0B; ii++)
  {
    LP5036.setBrightness(ii, 0xFF); // 256/256
    LP5036.setColor(ii*3,   0x00);
    LP5036.setColor(ii*3+1, 0x00);  
    LP5036.setColor(ii*3+2, 0xFF); // blue only
     delay(25);
  }
  delay(1000);
  
  // Turn off leds very quickly from 1 to 36 one at a time  
  for(uint8_t ii = 0x00; ii <=0x0B; ii++)
  {
    LP5036.setBrightness(ii, 0xFF);
    LP5036.setColor(ii*3,   0x00);
    LP5036.setColor(ii*3+1, 0x00);
    LP5036.setColor(ii*3+2, 0x00);
    delay(50);
  }
  delay(1000);

 LP5036.bankControlOn(); // change to controlling rgb channels together for each rgb led
 LP5036.bankColor(0x00, 0x00, 0xFF);
 
 // Breath all leds slowly
  allLEDFadeOn(100);
  allLEDFadeOff(100);
  // then faster
  allLEDFadeOn(50);
  allLEDFadeOff(50);
  //then faster still
  allLEDFadeOn(10);
  allLEDFadeOff(10);
  //then smooth blink
  allLEDFadeOn(5);
  allLEDFadeOff(5);
  allLEDFadeOn(5);
  allLEDFadeOff(5);
  allLEDFadeOn(5);
  allLEDFadeOff(5);
  delay(1000);

  for (color = 0; color < 255; color++) { // Slew through the color spectrum

    hueToRGB(color, brightness);  // call function to convert hue to RGB

     LP5036.bankBrightness(0x80); // set all leds to 1/2 output
    // write the RGB values to the pins
     LP5036.bankColor(R, G, B);
    delay(100);
  }

  LP5036.bankControlOff(); // change to controlling rgb channels individually

  // Fade on and fade off leds 1 to 12 one at a time
  for(uint8_t ii = 0x00; ii <=0x0B; ii++)
  {
    for (int8_t j=0; j<=63; j++) {// one LED breath rising
    LP5036.setColor(ii*3,   0x00);
    LP5036.setColor(ii*3+1, 0x00);  
    LP5036.setColor(ii*3+2, 0xFF); // blue only
    LP5036.setBrightness(ii, PWM_Gamma64[j]); // set all leds      
      delay(1);
    }
    for (int8_t j=63; j>=0; j--) {// all LED breath falling
    LP5036.setColor(ii*3,   0x00);
    LP5036.setColor(ii*3+1, 0x00);  
    LP5036.setColor(ii*3+2, 0xFF); // blue only
    LP5036.setBrightness(ii, PWM_Gamma64[j]); // set all leds      
     delay(3);
    }
  }
  delay(1000);
 

} /* end of main loop */

//Special customized functions *********************************************************
/*
void mode1(void)  // Taken from ISSI Arduino code
{
  int8_t i = 0;
  int8_t j = 0;

  for(i=1; i<=12; i++) // First third
  {
    LP5036.setPWM((i*3),0xFF); //set  PWM  
    LP5036.PWMUpdate();        //update PWM & control registers
    delay(80);//100ms
  }
  delay(500); //keep 0.5s
  
  for(i=1; i<=12; i++) // Second third
  {
    LP5036.setPWM((i*3 - 1),0xFF); //set  PWM  
    LP5036.PWMUpdate();      //update PWM & congtrol registers
    delay(80);//100ms
  }
  delay(500); //keep 0.5s
  
  for(i=1; i<=12; i++) // Last third
  {
    LP5036.setPWM((i*3 - 2),0xFF); //set  PWM  
    LP5036.PWMUpdate();      //update PWM & congtrol registers
    delay(80);//100ms
  }
  delay(500); //keep 0.5s

  for (j=63; j>=0; j--) //all LED breath falling 
  {
     for(i=1;i<=0x24;i++)
    {
      LP5036.setPWM(i,PWM_Gamma64[j]); //set all PWM 
    }
    LP5036.PWMUpdate();      //update PWM & congtrol registers
    delay(30);//20ms
  } 
  delay(500); //keep 0.5s
}
*/
void allLEDFadeOn(uint8_t speed) // fade speed in milliseconds
{
   for (int8_t j=0; j<=63; j++) // all LED breath rising
  {
    LP5036.bankBrightness(PWM_Gamma64[j]); // set all leds
    delay(speed); 
  } 
    delay(500); //keep 0.5s
}


void allLEDFadeOff(uint8_t speed) // fade speed in milliseconds
{
   for (int8_t j=63; j>=0; j--) // all LED breath falling
  {
    LP5036.bankBrightness(PWM_Gamma64[j]); // set all leds
    delay(speed); 
  } 
    delay(500); //keep 0.5s
}


// Courtesy http://www.instructables.com/id/How-to-Use-an-RGB-LED/?ALLSTEPS
// function to convert a color to its Red, Green, and Blue components.

void hueToRGB(uint8_t hue, uint8_t brightness)
{
    uint16_t scaledHue = (hue * 6);
    uint8_t segment = scaledHue / 256; // segment 0 to 5 around the
                                            // color wheel
    uint16_t segmentOffset =
      scaledHue - (segment * 256); // position within the segment

    uint8_t complement = 0;
    uint16_t prev = (brightness * ( 255 -  segmentOffset)) / 256;
    uint16_t next = (brightness *  segmentOffset) / 256;

    if(invert)
    {
      brightness = 255 - brightness;
      complement = 255;
      prev = 255 - prev;
      next = 255 - next;
    }

    switch(segment ) {
    case 0:      // red
        R = brightness;
        G = next;
        B = complement;
    break;
    case 1:     // yellow
        R = prev;
        G = brightness;
        B = complement;
    break;
    case 2:     // green
        R = complement;
        G = brightness;
        B = next;
    break;
    case 3:    // cyan
        R = complement;
        G = prev;
        B = brightness;
    break;
    case 4:    // blue
        R = next;
        G = complement;
        B = brightness;
    break;
   case 5:      // magenta
    default:
        R = brightness;
        G = complement;
        B = prev;
    break;
    }
}

