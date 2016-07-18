/**
 * The MySensors Arduino library handles the wireless radio link and protocol
 * between your home built sensors/actuators and HA controller of choice.
 * The sensors forms a self healing radio network with optional repeaters. Each
 * repeater and gateway builds a routing tables in EEPROM which keeps track of the
 * network topology allowing messages to be routed to nodes.
 *
 * Created by Henrik Ekblad <henrik.ekblad@mysensors.org>
 * Copyright (C) 2013-2015 Sensnology AB
 * Full contributor list: https://github.com/mysensors/Arduino/graphs/contributors
 *
 * Documentation: http://www.mysensors.org
 * Support Forum: http://forum.mysensors.org
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 *******************************
 *
 * DESCRIPTION
 * <template>
 * <connecting sketch>
 * 
 * VERSION
 * <0.0>
 * 
 * DEPENDENCIES
 * Arduino Built-in libraries
 * MySensors
 * SPI
 * <libraries>
 * 
 * CONTRIBUTORS
 * <name email>
 * 
 * LICENCE
 * GPL v2
 * (libraries may have other licences)
 *
 */

// Enable debug prints
#define MY_DEBUG

// Enable and select radio type attached
#define MY_RADIO_NRF24
//#define MY_RADIO_RFM69

// Define SENSOR IDs
#define CHILD_ID_<NAME>

// Define GPIO PINS
#define <NAME>_PIN_ANALOG <PIN_NBR>
#define <NAME>_PIN_DIGITAL <PIN_NBR>


#include <SPI.h>
#include <MySensors.h>

unsigned long SLEEP_TIME = 30*1000; // Sleep time between reads (in milliseconds)


MyMessage <MSGNAME>(CHILD_ID_<NAME>, <V_TYPE>);

void presentation() {
  // Send the sketch version information to the gateway and Controller
  sendSketchInfo("<NODE_NAME>", "<VERSION>");

  // Register all sensors to gateway (they will be created as child devices)
	present(CHILD_ID_<NAME>, <S_TYPE>);  
}

void loop() {
	
	// Get value from Sensor and send value to controler
	send(<MSGNAME>.set(<V_TYPE_VALUE>));
	
	sleep(SLEEP_TIME);
}




