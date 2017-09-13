#include "Arduino.h"
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

void pinMode(uint8_t pin, uint8_t mode) {
   mock().actualCall("pinMode").withParameter("pin", pin).withParameter("mode", mode);
}

void digitalWrite(uint8_t pin, uint8_t state) {
   mock().actualCall("digitalWrite").withParameter("pin", pin).withParameter("state", state);
}

static unsigned long millis_value = 0;
unsigned long millis(void) {
   return millis_value;
}
void setMillis(unsigned long t) {
   millis_value = t;
}

