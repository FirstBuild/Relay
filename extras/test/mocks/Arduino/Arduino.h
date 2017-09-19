/*
 * Arduino.h
 *
 * A (possibly incompatible) mock header for testing Arduino code.
 */

#ifndef ARDUINO_H
#define ARDUINO_H

#include <stdint.h>

#define LOW 0
#define HIGH 1
#define OUTPUT 1

void pinMode(uint8_t, uint8_t);
void digitalWrite(uint8_t, uint8_t);

void setMillis(unsigned long t);
unsigned long millis(void);

#endif // ARDUINO_H

