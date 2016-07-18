/*
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
 *
 *  MH-Z14 CO2 sensor
 * 
 *  Wiring:
 *   Pad 1, Pad 5: Vin (Voltage input 4.5V-6V) 
 *   Pad 2, Pad 3, Pad 12: GND 
 *   Pad 6: PWM output ==> pin 6
 *
 *	From: http://davidegironi.blogspot.fr/2014/01/co2-meter-using-ndir-infrared-mh-z14.html
 * 	  MH-Z14 has a PWM output, with a sensitivity range of 0ppm to 2000ppm CO2, an accurancy of ±200ppm.
 * 	  The cycle is 1004ms±5%, given the duty cicle Th (pulse high), Tl is 1004-Th, we can convert it to CO2 value using the formula:
 *	  CO2ppm = 2000 * (Th - 2ms) /(Th + Tl - 4ms)
 * 	From: http://airqualityegg.wikispaces.com/Sensor+Tests
 *	  - response time is less than 30 s
 *   - 3 minute warm up time
 *	datasheet: http://www.futurlec.com/Datasheet/Sensor/MH-Z14.pdf
 * Contributor: epierre
 */

// Enable debug prints to serial monitor
#define MY_DEBUG 

// Enable and select radio type attached
#define MY_RADIO_NRF24
//#define MY_RADIO_RFM69

#include <SPI.h>
#include <MySensors.h> 
#include <DHT.h>

#define ID_HUM 0
#define ID_TEMP 1

#define PIN_SENSOR 3

unsigned long SLEEP_TIME = 30*1000; // Sleep time between reads (in milliseconds)

DHT dht(PIN_SENSOR, DHT22);
float lastHum;
float lastTemp;

MyMessage msgHum(ID_HUM, V_HUM);
MyMessage msgTemp(ID_TEMP, V_TEMP);

void setup()  
{
  dht.begin();
}

void presentation() {
  // Send the sketch version information to the gateway and Controller
  sendSketchInfo("Hum and Temp", "1.0-2.0");

  // Register all sensors to gateway (they will be created as child devices)
  present(ID_HUM, S_HUM);
  present(ID_TEMP, S_TEMP);
}

void loop() { 

  float hum = dht.readHumidity();
  if (isnan(hum)) {
    Serial.println("Failed reading humidity from DHT");
  } else if (hum != lastHum) {
    lastHum = hum;
    Serial.print("Hum: ");
    Serial.println(hum);
    send(msgHum.set((int)hum));
  }
  
  float temp = dht.readTemperature();
  if (isnan(temp)) {
    Serial.println("Failed reading temperature from DHT");
  } else if (hum != lastTemp) {
    lastTemp = temp;
    Serial.print("Temp: ");
    Serial.println(temp);
    send(msgTemp.set((int)temp));
  }
  
  
  // Power down the radio.  Note that the radio will get powered back up
  // on the next write() call.
  sleep(SLEEP_TIME); //sleep for: sleepTime
}
