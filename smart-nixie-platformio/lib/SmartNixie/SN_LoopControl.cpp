#include "SN_LoopControl.h"

SN_LoopControl::SN_LoopControl() {
    clock = SN_Clock(disp);
    sensor = SN_Sensor(disp);

    // TODO: timezone/manual imp after iotwebconf
    adjustRTC();
}

void SN_LoopControl::doLoop(int mode) {

    switch (mode) {
    case 1 : clock.displayCurrentTime();
        break;
    case 2 : sensor.displayCurrentValues();
        break;
    default:
        break;
    }

}

void SN_LoopControl::adjustRTC() {
    clock.setRTCDateTime(DateTime(2020, 4, 5, 12, 30, 0));
}
