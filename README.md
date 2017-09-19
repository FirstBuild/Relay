# Relay
Control a relay with a period and duty cycle.

This module was developed to enable the use of a relay with PID control.
This can be accomplished by using the PID loop to control the duty cycle
of the relay.

### Basic Usage

To use Relay, create an instance and set the state to running:
```
#define RELAY_PIN 7
#define RELAY_PERIOD 30
Relay relay(RELAY_PIN, RELAY_PERIOD);

void setup() {
   relay.setRelayMode(relayModeAutomatic);
}
```

Call the loop function to excercise the relay:
```
void loop() {
   relay.loop();
}
```

### Function Reference:


```
void setRelayMode(RelayMode state);
```
Call `setRelayMode` with `relayModeManual` or `relayModeAutomatic`
- `relayModeManual` - Turns the relay off and disables the relay from automatic operation.  Use this state for manual operation of the relay.
- `relayModeAutomatic` - Starts automatic operation of the relay using the period and duty cycle.

```
RelayMode getRelayMode(void);
```
Returns the state of the relay, `relayModeManual` or `relayModeAutomatic`.

```
void setRelayPosition(RelayPosition position);
```
Set the relay position:
- `relayPositionOpen` - The relay contacts are open.
- `relayPositionClosed` - The relay contacts are closed.

```
RelayPosition getRelayPosition(void);
```
Get the position of the relay, `relayPositionOpen` or `relayPositionClosed`.

```
void setDutyCyclePercent(double dutyCycle);
```
Set the duty cycle of the relay.  `dutyCycle` must be between 0.0 and 1.0 inclusive.

```
double getDutyCyclePercent(void);
```
Get the duty cycle of the relay.

```
    void setPeriodInSeconds(uint16_t periodInSeconds);
```
Set the period of opertion of the relay in seconds.

```
    uint16_t getPeriodInSeconds(void);
```
Get the period of the operation of the relay in seconds.

### Testing

To run the tests:

```
cd extras
make -f tdd_tests.mk
```

To generate test coverage reports:

```
./gen_cov_report.sh
```

An HTML test coverage report will be placed in the `extras/output` directory.

