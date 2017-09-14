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

Relay::Relay(uint8_t pin, uint16_t periodInSeconds): _pin(pin), _periodInSeconds(periodInSeconds) {
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, LOW);
    _dutyCycle = 0.5;
    _state = relayStateIdle;
    _position = relayPositionOpen;
}

void Relay::setRelayState(RelayState state) {
   switch (state) {
      case relayStateIdle:
         _state = state;
         setRelayPosition(relayPositionOpen);
         break;
      case relayStateRunning:
         if (relayStateRunning != _state) {
            _state = state;
            _periodTime = 0;
            _oldTime = millis();
         }
         break;
   }
}

RelayState Relay::getRelayState(void) {
   return _state;
}

void Relay::setRelayPosition(RelayPosition position) {
   switch(position) {
      case relayPositionOpen:
      case relayPositionClosed:
         _position = position;
         digitalWrite(_pin, _position);
         break;
   }
}

RelayPosition Relay::getRelayPosition(void) {
  return _position;
}

void Relay::setDutyCyclePercent(double dutyCycle) {
   if ((dutyCycle >= 0.0) && (dutyCycle <= 1.0)) {
      _dutyCycle = dutyCycle;
   }
}

double Relay::getDutyCyclePercent(void) {
   return _dutyCycle;  
}

void Relay::updateRelay(void) {
   uint32_t newTime = millis();
   uint32_t offTime = _periodInSeconds * 1000 * _dutyCycle;

   if (_state == relayStateIdle) {
      return;
   }

   if (newTime < _oldTime) {
      _periodTime += (UINT32_MAX - _oldTime + newTime);
   } else {
      _periodTime += (newTime - _oldTime);
   }
   _oldTime = newTime;

   if (_periodTime < offTime) {
      if (_dutyCycle > 0.0) setRelayPosition(relayPositionClosed);
   } else if (_periodTime >= _periodInSeconds*1000) {
      _periodTime = 0;
      if (_dutyCycle > 0.0) setRelayPosition(relayPositionClosed);
   } else {
      setRelayPosition(relayPositionOpen);
   }
}

