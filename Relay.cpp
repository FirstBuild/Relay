/*
 * Relay.h
 * 
 * Implement a relay controlled by duty cycle.
 * 
 * Author: Rob Bultman
 *         Sept. 13, 2017
 */

#include "Relay.h"
#include <Arduino.h>

Relay::Relay(int pin, uint16_t periodInSeconds): _pin(pin), _periodInSeconds(periodInSeconds) {
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, LOW);
}

void Relay::setRelayState(RelayState state) {
  
}

RelayState Relay::getRelayState(void) {
  
}

void Relay::setRelayPosition(RelayPosition position) {
  
}

RelayPosition Relay::getRelayPosition(void) {
  
}

void Relay::setDutyCyclePercent(double dutyCycle) {
  
}

void Relay::updateRelay(void) {
  
}

