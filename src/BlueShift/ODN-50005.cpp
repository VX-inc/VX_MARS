/*!
 * @file ODN_50005.cpp
 *
 * This library is written for the V.X. Inc. BlueShift ODN-50005 Imaging Sensor Module
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
#include "ODN-50005.h"
#include "Wire.h"

//ODN-50005 Defines
#define ODN50005_WHITE_LED_PIN          5
#define ODN50005_FAR_RED_LED_PIN        6
#define ODN50005_I2C_EXPANDER_ADDRESS   0x20
#define ODN50005_UP_BUTTON_BIT          0
#define ODN50005_DOWN_BUTTON_BIT        4

bool i2c_expander_connected = false;
bool ir_led_is_on = false;
bool white_led_is_on = false;
int button_hold_time = 0;


//////////// BLUSHIFT FUNCITONS ///////////////
  
bool BlueShift_ODN50005::init(uint16_t hold_time) {
  Wire.begin();
  Wire.beginTransmission(ODN50005_I2C_EXPANDER_ADDRESS );
  byte error = Wire.endTransmission();
  button_hold_time = hold_time;

  if (error == 0) {
    i2c_expander_connected = true;
    pinMode(ODN50005_WHITE_LED_PIN, OUTPUT);
    pinMode(ODN50005_FAR_RED_LED_PIN, OUTPUT);
  }
    return i2c_expander_connected;
  }  

button_state_t BlueShift_ODN50005::buttonManager(void){
  bool upButtonState = upButtonPressed();
  bool downButtonState = downButtonPressed();
  static bool upButtonLastState = false;
  static bool downButtonLastState = false;
  static bool doubleButtonPressed = false;
  unsigned long upHoldTime;
  unsigned long downHoldTime;
  button_state_t retVal = BUTTON_NO_PRESS;

  if (upButtonState && !upButtonLastState) {
    upHoldTime = millis();
  }

  if (downButtonState && !downButtonLastState) {
    downHoldTime = millis();
  }


  if ((!downButtonState || !upButtonState) && downButtonLastState && upButtonLastState) {
    doubleButtonPressed = true;
	retVal = BUTTON_BOTH_PRESS;
  }

  if (!upButtonState && upButtonLastState && !downButtonState && !doubleButtonPressed) {
    upHoldTime = millis() - upHoldTime;
    if (upHoldTime > 50) {  //50ms debounce
      if (upHoldTime < button_hold_time) { //long hold compare
		retVal = BUTTON_SHORT_UP;
      } else {
		retVal = BUTTON_LONG_UP;
      }
    }
  }

  if (!downButtonState && downButtonLastState && !upButtonState && !doubleButtonPressed) {
    downHoldTime = millis() - downHoldTime;
    if (downHoldTime > 50) {  //50ms debounce
      if (downHoldTime < button_hold_time) {  //long hold compare
		retVal = BUTTON_SHORT_DOWN;
      } else {
		retVal = BUTTON_LONG_DOWN;
      }
    }
  }

  if (!downButtonState && !upButtonState){
    doubleButtonPressed = false;
  }

  upButtonLastState = upButtonState;
  downButtonLastState = downButtonState;

  return retVal;
}

  /* Integers from 0 to 255, 0 is off, 255 is full brightness 
  *  both White and IR LEDs cannot be on at the same time, must shut off the other LED first.
  */
void BlueShift_ODN50005::setWhiteLED(uint8_t brightness) {
    analogWrite(ODN50005_FAR_RED_LED_PIN, 0);
    ir_led_is_on = false;
    analogWrite(ODN50005_WHITE_LED_PIN, brightness);
    if(brightness > 0){
      white_led_is_on = true;
    } else {
      white_led_is_on = false;
    }
  }

  /* Integers from 0 to 255, 0 is off, 255 is full brightness 
  *  both White and IR LEDs cannot be on at the same time, must shut off the other LED first.
  */
void BlueShift_ODN50005::setInfraredLED(uint8_t brightness) {
    analogWrite(ODN50005_WHITE_LED_PIN, 0);
    white_led_is_on = false;
    analogWrite(ODN50005_FAR_RED_LED_PIN, brightness);
    if(brightness > 0){
      ir_led_is_on = true;
    } else {
      ir_led_is_on = false;
    }
  }

bool BlueShift_ODN50005::whiteLEDIsOn(void){
  return white_led_is_on;
} 

bool BlueShift_ODN50005::infraredLEDIsOn(void){
  return ir_led_is_on;
} 

bool BlueShift_ODN50005::upButtonPressed(void) {
    if (i2c_expander_connected) {
      Wire.requestFrom(ODN50005_I2C_EXPANDER_ADDRESS, 1);
      uint8_t readPacket;
      while (Wire.available()) {
        readPacket = Wire.read();
      }
      return !(0x01 & (readPacket >> ODN50005_UP_BUTTON_BIT));
    } else {
    return false;
	}
  }

  bool BlueShift_ODN50005::downButtonPressed(void) {
    if (i2c_expander_connected) {
      Wire.requestFrom(ODN50005_I2C_EXPANDER_ADDRESS, 1);
      uint8_t readPacket;
      while (Wire.available()) {
        readPacket = Wire.read();
      }
      return !(0x01 & (readPacket >> ODN50005_DOWN_BUTTON_BIT));
    } else {
    return false;
	}
}
