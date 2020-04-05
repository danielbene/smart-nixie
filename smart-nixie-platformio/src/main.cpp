#include <Arduino.h>
#include "SN_Clock.h"

//#define DELAY 350
#define DELAY 2000

SN_Clock snClock;
unsigned long loopTs;

void setup() {
  Serial.begin(9600);
  loopTs = millis() + DELAY;
  snClock.setCountDown(1);

  snClock.setRTCDateTime(DateTime(2020, 4, 5, 12, 30, 0));
}

void loop() {

  // non-blocking delay
  if (millis() >= loopTs) {
    //snClock.displayCurrentTime();
    snClock.doCountDownLoop();
    loopTs = millis() + DELAY;
  }
}
