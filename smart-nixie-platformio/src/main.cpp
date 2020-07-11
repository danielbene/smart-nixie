#include <Arduino.h>

#include "SN_IotWebConf.h"
#include "SN_LoopControl.h"
#include "Util.h"

// NOTE: missing includes has to be installed from PIO library manager!

//#define DELAY 250
#define DELAY 1500

DateTime countUpStart;
DateTime countDownEnd;
SN_LoopControl::Mode mode;
SN_IotWebConf snIotWebConf = SN_IotWebConf(&mode, &countUpStart, &countDownEnd);
SN_LoopControl snLoopControl = SN_LoopControl(&countUpStart, &countDownEnd);

unsigned long loopTs = millis() + DELAY;

boolean timeCheck() {
    if (snIotWebConf.getIsTimeParamsUpdated()) {
        if (snIotWebConf.getIsAutoTime()) {
            // TODO: web based time setup
        } else {
            snLoopControl.adjustRTC(snIotWebConf.getDateTimeParam());
        }

        snIotWebConf.setTimeParamsUpdated(false);
        return true;
    }

    return !snLoopControl.isRTCLostPower();
}

void setup() {
    if (Util::DEBUG) Serial.begin(115200);
    snIotWebConf.setup();
}

void loop() {
    snIotWebConf.doLoop();

    if (millis() >= loopTs) {
        if (!timeCheck()) mode = SN_LoopControl::Mode::ERROR;

        snLoopControl.doLoop(mode);
        loopTs = millis() + DELAY;
    }
}
