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

boolean timeUpdateCheck() {
    return snLoopControl.timeUpdate(&snIotWebConf.isTimeParamsUpdated,
        snIotWebConf.isAutoTime, snIotWebConf.getDateTimeParam());
}

void setup() {
    if (Util::DEBUG) Serial.begin(115200);
    snIotWebConf.setup();
}

void loop() {
    snIotWebConf.doLoop();

    if (millis() >= loopTs) {
        // TODO: timeUpdateCheck do not needed in every loop - maybe through onConfigChanged callback?
        if (!timeUpdateCheck()) mode = SN_LoopControl::Mode::ERROR;

        snLoopControl.doLoop(mode);
        loopTs = millis() + DELAY;
    }
}
