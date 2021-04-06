/*!
 * @file MARS.cpp
 *
 * This library is written for the VX Inc. BlueShift headset to enable 
 * user applications.  This library includes references to hardware that 
 * may or may not be installed on the headset depending on the configuration.
 * 
 * Please insure that all devices that are referenced in code are attached to
 * the headset before use. 
 * 
 * This codebase is maintained at the following address. 
 * <https://github.com/VX-inc/VX_MARS>.
 *
 * For more information about the hardware referenced, please visit
 * <https://www.vx-inc.com/>
 * 
 */

#include "Arduino.h"
#include "MARS.h"

//MARS Defines
#define MARS_BRIGHTNESS_PIN        11
#define MARS_ALS_PIN               A0

//////////// MARS FUNCITONS ///////////////

void MARS::init(void) {
  pinMode(MARS_BRIGHTNESS_PIN, OUTPUT);
  pinMode(MARS_ALS_PIN, INPUT);
}

/* Integers from 0 to 10, 0 is off, 10 is full brightness */
  void MARS::setDisplayBrightness(uint8_t brightness) {
    if (brightness <= 10) {
      analogWrite(MARS_BRIGHTNESS_PIN, brightness * 10 + 15);
    }
  }

uint16_t MARS::getALSValue(void) {
    return analogRead(MARS_ALS_PIN);
}
