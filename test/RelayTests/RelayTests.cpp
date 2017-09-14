#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include <stdint.h>
#include "Relay.h"
#include "Arduino.h"

using namespace std;

extern "C"
{
}

TEST_GROUP(RelayTests)
{
   void setup()
   {
      mock().ignoreOtherCalls();
   }

   void teardown()
   {
   }
};

TEST(RelayTests, constructor)
{
   Relay *pRelay;

   mock().expectOneCall("pinMode").withParameter("pin", 1).withParameter("mode", OUTPUT);
   mock().expectOneCall("digitalWrite").withParameter("pin", 1).withParameter("state", LOW);
   pRelay = new Relay(1, 30);
   mock().checkExpectations();

   CHECK_EQUAL(relayPositionOpen, pRelay->getRelayPosition());
   CHECK_EQUAL(relayStateIdle, pRelay->getRelayState());
   DOUBLES_EQUAL(0.5, pRelay->getDutyCyclePercent(), 0.0001);

   delete pRelay;
}

TEST(RelayTests, setPositionClosed)
{
   Relay relay(1, 30);

   mock().expectOneCall("digitalWrite").withParameter("pin", 1).withParameter("state", HIGH);
   relay.setRelayPosition(relayPositionClosed);
   CHECK_EQUAL(relayPositionClosed, relay.getRelayPosition());
}

TEST(RelayTests, setPositionOpen)
{
   Relay relay(1, 30);
   relay.setRelayPosition(relayPositionClosed);

   mock().expectOneCall("digitalWrite").withParameter("pin", 1).withParameter("state", LOW);
   relay.setRelayPosition(relayPositionOpen);
   CHECK_EQUAL(relayPositionOpen, relay.getRelayPosition());
}

TEST(RelayTests, setRelayState)
{
   Relay relay(1, 30);

   relay.setRelayState(relayStateRunning);
   CHECK_EQUAL(relayStateRunning, relay.getRelayState());
   relay.setRelayState(relayStateIdle);
   CHECK_EQUAL(relayStateIdle, relay.getRelayState());
}

TEST(RelayTests, setDutyCycle)
{
   Relay relay(1, 30);

   relay.setDutyCyclePercent(0.75);
   DOUBLES_EQUAL(0.75, relay.getDutyCyclePercent(), 0.0001);
}

TEST(RelayTests, setDutyCycleIgnoresOutOfRangeInput)
{
   Relay relay(1, 30);

   relay.setDutyCyclePercent(1.1);
   DOUBLES_EQUAL(0.5, relay.getDutyCyclePercent(), 0.0001);
   relay.setDutyCyclePercent(-1.0);
   DOUBLES_EQUAL(0.5, relay.getDutyCyclePercent(), 0.0001);
}

TEST(RelayTests, settingStateToIdleTurnsOffRelay)
{
   Relay relay(1, 30);
   relay.setRelayState(relayStateRunning);
   relay.setRelayPosition(relayPositionClosed);

   mock().expectOneCall("digitalWrite").withParameter("pin", 1).withParameter("state", LOW);
   relay.setRelayState(relayStateIdle);
}

TEST(RelayTests, relayTurnsOnAtStartOfPeriod)
{
   Relay relay(1, 30);
   setMillis(1);
   relay.setRelayState(relayStateRunning);
   mock().expectOneCall("digitalWrite").withParameter("pin", 1).withParameter("state", HIGH);
   relay.updateRelay();
   CHECK_EQUAL(relayPositionClosed, relay.getRelayPosition());
}

TEST(RelayTests, relayTurnsOffAtEndOfDutyCycle)
{
   Relay relay(1, 30);
   setMillis(0);
   relay.setRelayState(relayStateRunning);
   relay.updateRelay();
   setMillis(14999);
   CHECK_EQUAL(relayPositionClosed, relay.getRelayPosition());
   setMillis(15000);
   mock().expectOneCall("digitalWrite").withParameter("pin", 1).withParameter("state", LOW);
   relay.updateRelay();
   CHECK_EQUAL(relayPositionOpen, relay.getRelayPosition());
}

TEST(RelayTests, relayTurnsBackOnAtEndOfPeriod)
{
   Relay relay(1, 30);
   setMillis(0);
   relay.setRelayState(relayStateRunning);
   relay.updateRelay();
   setMillis(29999);
   relay.updateRelay();
   CHECK_EQUAL(relayPositionOpen, relay.getRelayPosition());
   setMillis(30000);
   mock().expectOneCall("digitalWrite").withParameter("pin", 1).withParameter("state", HIGH);
   relay.updateRelay();
   CHECK_EQUAL(relayPositionClosed, relay.getRelayPosition());
}

TEST(RelayTests, relayShouldNotTurnOnIfDutyCycleIsZero)
{
   Relay relay(1, 30);
   relay.setDutyCyclePercent(0.0);
   setMillis(0);
   relay.setRelayState(relayStateRunning);
   relay.updateRelay();
   CHECK_EQUAL(relayPositionOpen, relay.getRelayPosition());
}


TEST(RelayTests, checkForRollover)
{
   Relay relay(1, 30);
   setMillis(UINT32_MAX-15000);
   relay.setRelayState(relayStateRunning);
   relay.updateRelay();
   CHECK_EQUAL(relayPositionClosed, relay.getRelayPosition());
   setMillis(UINT32_MAX-1);
   relay.updateRelay();
   CHECK_EQUAL(relayPositionClosed, relay.getRelayPosition());
   setMillis(UINT32_MAX);
   relay.updateRelay();
   CHECK_EQUAL(relayPositionOpen, relay.getRelayPosition());
   setMillis(14999);
   relay.updateRelay();
   CHECK_EQUAL(relayPositionOpen, relay.getRelayPosition());
   setMillis(15000);
   relay.updateRelay();
   CHECK_EQUAL(relayPositionClosed, relay.getRelayPosition());
}

TEST(RelayTests, ifIdleOutputDoesNotChange)
{
   Relay relay(1, 30);
   setMillis(0);
   relay.setRelayState(relayStateRunning);
   relay.updateRelay();
   CHECK_EQUAL(relayPositionClosed, relay.getRelayPosition());
   setMillis(1500);
   relay.updateRelay();
   CHECK_EQUAL(relayPositionClosed, relay.getRelayPosition());
   relay.setRelayState(relayStateIdle);
   relay.updateRelay();
   CHECK_EQUAL(relayPositionOpen, relay.getRelayPosition());
   setMillis(31000);
   relay.updateRelay();
   CHECK_EQUAL(relayPositionOpen, relay.getRelayPosition());
}

TEST(RelayTests, ifIdleSettingRelayPositionWorks)
{
   Relay relay(1, 30);
   setMillis(0);
   relay.setRelayState(relayStateIdle);
   relay.updateRelay();
   CHECK_EQUAL(relayPositionOpen, relay.getRelayPosition());
   setMillis(16000);
   relay.setRelayPosition(relayPositionClosed);
   relay.updateRelay();
   CHECK_EQUAL(relayPositionClosed, relay.getRelayPosition());
   relay.setRelayPosition(relayPositionOpen);
   setMillis(31000);
   relay.updateRelay();
   CHECK_EQUAL(relayPositionOpen, relay.getRelayPosition());
}

