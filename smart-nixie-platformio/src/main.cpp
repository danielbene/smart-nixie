#include <Arduino.h>

#include "config.h"
#include "SN_IotWebConf.h"
#include "SN_LoopControl.h"
#include "Util.h"

// NOTE: missing includes has to be installed from PIO library manager!

DateTime countUpStart;
DateTime countDownEnd;
SN_LoopControl::Mode mode;
SN_IotWebConf snIotWebConf = SN_IotWebConf(&mode, &countUpStart, &countDownEnd);
SN_LoopControl snLoopControl = SN_LoopControl(&countUpStart, &countDownEnd, &snIotWebConf.isConnected);

unsigned long loopTs = millis() + TICK_MS;
boolean isTimeSet = false;

boolean timeUpdateCheck() {
    return snLoopControl.timeUpdate(&snIotWebConf.isTimeParamsUpdated,
        snIotWebConf.isAutoTime, snIotWebConf.getDateTimeParam(), snIotWebConf.getT);
}

void setup() {
    if (DEBUG) Serial.begin(SERIAL_SPEED);
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
        loopTs = millis() + TICK_MS;
    }

}
