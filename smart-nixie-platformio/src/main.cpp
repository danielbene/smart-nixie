#include <Arduino.h>

#include "SN_IotWebConf.h"
#include "SN_LoopControl.h"

// NOTE: missing includes has to be installed from PIO library manager!

//#define DELAY 250
#define DELAY 1500

DateTime countUpStart;
SN_LoopControl::Mode mode;
SN_IotWebConf snIotWebConf = SN_IotWebConf(&mode, &countUpStart);
SN_LoopControl snLoopControl = SN_LoopControl(&countUpStart);

unsigned long loopTs = millis() + DELAY;
boolean isTimeSet = !snLoopControl.isRTCLostPower();

void setup() {
    Serial.begin(115200);

    snIotWebConf.setup();
}

void loop() {
    snIotWebConf.doLoop();

    if (snIotWebConf.getIsTimeParamsUpdated()) {
        if (snIotWebConf.getIsAutoTime()) {
            // TODO: web based time setup
        } else {
            snLoopControl.adjustRTC(snIotWebConf.getDateTimeParam());
        }

        snIotWebConf.setTimeParamsUpdated(false);
        isTimeSet = true;
    }

    if (millis() >= loopTs) {
        if (!isTimeSet) {
            mode = SN_LoopControl::Mode::ERROR;
        }

        snLoopControl.doLoop(mode);
        loopTs = millis() + DELAY;
    }
}
