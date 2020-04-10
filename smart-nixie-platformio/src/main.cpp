#include <Arduino.h>
#include "SN_LoopControl.h"

//#define DELAY 350
#define DELAY 1500

unsigned long loopTs = millis() + DELAY;
SN_LoopControl snLoopControl = SN_LoopControl();

boolean test = false;

void setup() {
  Serial.begin(115200);



  //snClock.setCountDown(1);
}

void loop() {

  // non-blocking delay
  if (millis() >= loopTs) {
    //snClock.displayCurrentTime();
    //snClock.doCountDownLoop();
    //snSensor.testRead();

    if (test) {
      snLoopControl.doLoop(1);
    } else {
      snLoopControl.doLoop(2);
    }

    test = !test;


    loopTs = millis() + DELAY;
  }
}
