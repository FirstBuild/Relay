/*
 * Basic Relay use example.
 * 
 * Author: Rob Bultman
 *         FirstBuild
 *         https://firstbuild.com/
 *         
 * Date: September 17, 2017
 *         
 * License: MIT
 */
#include <Relay.h>

// Create a relay on pin 7 with a 5 second period.  
// Use the default 50% duty cycle.
Relay relay(7, 5);

// Keep track of the relay position so we can time it.
RelayPosition currentPosition;

uint32_t oldTime;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  relay.setRelayMode(relayModeAutomatic);
  oldTime = millis();
  currentPosition = relay.getRelayPosition();
}

void loop() {
  RelayPosition newPosition = relay.getRelayPosition();
  uint32_t newTime;
  uint32_t deltaTime;

  // you must call loop in order to exercise the relay
  relay.loop();

  // Check the relay timing
  if (currentPosition != newPosition) {
    newTime = millis();
    deltaTime = newTime - oldTime;
    oldTime = newTime;

    Serial.print("Relay was ");
    if (currentPosition == relayPositionOpen) Serial.print("open ");
    else Serial.print("closed ");
    Serial.print("for ");
    Serial.print(deltaTime);
    Serial.println(" milliseconds.");

    currentPosition = newPosition;
  }
}
