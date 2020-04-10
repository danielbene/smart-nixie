#include "SN_LoopControl.h"

SN_LoopControl::SN_LoopControl() {
    clock = SN_Clock(disp);
    sensor = SN_Sensor(disp);

    adjustRTC();
}

// this is the main logic node - displayed numbers gets decided here
void SN_LoopControl::doLoop(SN_LoopControl::Mode mode) {

    if (mode == SN_LoopControl::Mode::CLOCK) {
        clock.displayCurrentTime();
    } else if (mode == SN_LoopControl::Mode::COUNTUP) {
        clock.setCountUp();
        // TODO doCountUpLoop
    } else if (mode == SN_LoopControl::Mode::COUNTDOWN) {
        // TODO countdown value set - blocked by web UI
        clock.setCountDown(1);
        clock.doCountDownLoop();
    } else if (mode == SN_LoopControl::Mode::SENSOR) {
        sensor.displayCurrentValues();
    } else if (mode == SN_LoopControl::Mode::ERROR) {
        // TODO error handling
    } else if (mode == SN_LoopControl::Mode::OFF) {
        disp.turnOff();
    } else {
        // TODO error - non-valid mode
    }

}

void SN_LoopControl::adjustRTC() {
    // TODO: timezone/manual impl after iotwebconf
    clock.setRTCDateTime(DateTime(2020, 4, 5, 12, 30, 0));
}
