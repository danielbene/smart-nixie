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
boolean isTimeSet = false;

boolean timeUpdateCheck() {
    return snLoopControl.timeUpdate(&snIotWebConf.isTimeParamsUpdated,
        snIotWebConf.isAutoTime, snIotWebConf.getDateTimeParam());
}

void setup() {
    if (Util::DEBUG) Serial.begin(115200);
    snIotWebConf.setup();

    isTimeSet = timeUpdateCheck();
}

void loop() {
    snIotWebConf.doLoop();

    if (millis() >= loopTs) {
        if (!isTimeSet || snIotWebConf.isTimeParamsUpdated) {
            mode = SN_LoopControl::Mode::ERROR;
            isTimeSet = timeUpdateCheck();
        }

        snLoopControl.doLoop(mode);
        loopTs = millis() + DELAY;

        Util::printDebugLine(snLoopControl.testNTPTime(), true);
    }
}
