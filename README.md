# VX_MARS

## Introduction
The VX modular augmented reality system (MARS) is available as a complete AR reference design. The MARS is a tested system that was designed to reduce lead time and development risk for new headset designs. A ready to manufacture package is available for users that have specific applications in mind.

MARS offers everything needed for USB Type-C PD negotiation, sensor integration, and onboard data processing for plug-n-play accessory modules. The reference supports two FHD CNED displays, 5 Gbit/s data bus, high-speed multiplexing, and full device control via the serial, MIPI, and I2C interfaces.

[learn more here](https://www.vx-inc.com)

## Firmware Integration
The MARS has a dedicated application microcontroller (ATMEGA32U4) designed to allow the user to program system functionality specific to their needs. The microcontroller is programmable over USB through the main device USB-C port. 

  Microcontroller can interface with:
  * Backlight brightness control 
  * Modules
  * Ambient Light Sensor (ALS)
  * USB Serial Port

To get started, download the MARS library above.

## Application Examples

### MARS_Barebones_Example
This is an example sketch for use with the barebones MARS Module.  

Hardware Required: 1 CNED installed.

This application demonstrates the following:
 * Ambient light sensor for CNED brightness control
 * Serial port communication for system state
 
### ODN-50005_Example
This is an example sketch for use with the ODN-50005 Image Sensor Module.  
 
Hardware Required: Base BlueShift headset, an ODN-50005 module installed in the
right accessory bay, and at least 1 CNED installed.

 This application demonstrates the following:
 * Short button presses increase and decrease the display brightness
 * Long button presses turn on and off the White and IR LEDs
 * Double button press switches to the ambient light sensor for CNED brightness control
 * Serial port communication for system state
 
 #### Important Note
 Please do not manipulate the individual ports without knowledge, this could cause damage to the hardware.


