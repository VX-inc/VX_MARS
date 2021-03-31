/*!
 * @file MARS.h
 *
 * This library is written for the VX Inc. BlueShift headset to enable 
 * user applications.  This library includes references to hardware that 
 * may or may not be installed on the headset depending on the configuration.
 * 
 * Please insure that all devices that are referenced in code are attached to
 * the headset before use. 
 * 
 * This codebase is maintained at the following address. 
 * <https://github.com/VX-inc/VX_BlueShift-Application-Examples>.
 *
 * For more information about the hardware referenced, please visit
 * <https://www.vx-inc.com/>
 * 
 */

#ifndef MARS_h
#define MARS_h
#include "Arduino.h"

#define MARS_RIGHT_MODULE_D5 5
#define MARS_RIGHT_MODULE_D6 6
#define MARS_FRONT_MODULE_D7 7
#define MARS_FRONT_MODULE_D8 8
#define MARS_LEFT_MODULE_D9  9
#define MARS_LEFT_MODULE_D10 10

class MARS
{
public:
    void init(void);
	void setDisplayBrightness(uint8_t brightness);
    uint16_t getALSValue(void);
private:
};

#endif
