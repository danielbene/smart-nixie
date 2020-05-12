#include <Arduino.h>
#include "SN_IotWebConf.h"
#include "SN_LoopControl.h"

//#define DELAY 250
#define DELAY 1500

SN_IotWebConf snIotWebConf = SN_IotWebConf();
SN_LoopControl snLoopControl = SN_LoopControl();
SN_LoopControl::Mode mode;

unsigned long loopTs = millis() + DELAY;
boolean test = false;

void setup() {
  Serial.begin(115200);

  snIotWebConf.setup();

  Serial.println("IotWebConfParams: ");
  Serial.println(snIotWebConf.getDateTimeParam());
  Serial.println(snIotWebConf.getMac1Param());
}

void loop() {
  snIotWebConf.doLoop();

  // non-blocking delay
  if (millis() >= loopTs) {
    if (test) {
      mode = SN_LoopControl::Mode::CLOCK;
    } else {
      mode = SN_LoopControl::Mode::SENSOR;
    }

    test = !test;

    snLoopControl.doLoop(mode);
    loopTs = millis() + DELAY;
  }

  //TODO: 30sec loop for mac address check?
  //TODO: hour loop for auto time correction?
}
