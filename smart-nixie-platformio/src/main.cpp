#include <Arduino.h>

#include "SN_IotWebConf.h"
#include "SN_LoopControl.h"
#include "Util.h"

DateTime countUpStart;
DateTime countDownEnd;
SN_LoopControl::Mode mode;
SN_IotWebConf snIotWebConf = SN_IotWebConf(&mode, &countUpStart, &countDownEnd);
SN_LoopControl snLoopControl = SN_LoopControl(snIotWebConf.getTZOffsetParam(), snIotWebConf.getDateTimeParam(), snIotWebConf.getSlotmachineTimeParam(), &countUpStart, &countDownEnd, &snIotWebConf.isConnected, &mode);

unsigned long loopTs = millis() + SN_TICK_MS;
boolean isTimeSet = false;

void setup() {
    if (SN_DEBUG) Serial.begin(SN_SERIAL_SPEED);
    snIotWebConf.setup();

    isTimeSet = snLoopControl.timeUpdate();
}

void loop() {
    snIotWebConf.doLoop();

    if (millis() >= loopTs) {
        if (!isTimeSet) {
            isTimeSet = snLoopControl.timeUpdate();
        } else if (strlen(snIotWebConf.getTZOffsetParam()) != 0 || strlen(snIotWebConf.getDateTimeParam()) != 0) {
            snLoopControl.timeParamUpdate();
        }

        snLoopControl.doLoop();
        loopTs = millis() + SN_TICK_MS;
    }

}
