/*
 * Relay.h
 * 
 * Implement a relay controlled by duty cycle.
 * 
 * Author: Rob Bultman
 *         Sept. 13, 2017
 */

#ifndef RELAY_H
#define RELAY_H

#include <stdint.h>

typedef enum {
  relayStateIdle,
  relayStateRunning
} RelayState;

typedef enum {
  relayPositionOpen,
  relayPositionClosed
} RelayPosition;

class Relay {
  public:
    Relay(int pin, uint16_t periodInSeconds);
    void setRelayState(RelayState state);
    RelayState getRelayState(void);
    void setRelayPosition(RelayPosition position);
    RelayPosition getRelayPosition(void);
    void setDutyCyclePercent(double dutyCycle);
    void updateRelay(void);

  private:
    int _pin;
    uint16_t _periodInSeconds;
    double _dutyCycle;
    RelayState state;
    RelayPosition position;
    uint32_t _periodTime;
};

#endif // RELAY_H
