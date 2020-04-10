#include <Arduino.h>
#include "SN_Clock.h"

//#define DELAY 350
#define DELAY 500

SN_Clock snClock;
unsigned long loopTs = millis() + DELAY;

void setup() {
  Serial.begin(115200);
  snClock.setRTCDateTime(DateTime(2020, 4, 5, 12, 30, 0));



  //snClock.setCountDown(1);
}

void loop() {

  // non-blocking delay
  if (millis() >= loopTs) {
    //snClock.displayCurrentTime();
    //snClock.doCountDownLoop();



    loopTs = millis() + DELAY;
  }
}
