#include "SN_LoopControl.h"

SN_LoopControl::SN_LoopControl() {
    clock = SN_Clock(&disp);
    sensor = SN_Sensor(&disp);
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
        disp.flash(9999);
    } else if (mode == SN_LoopControl::Mode::OFF) {
        disp.turnOff();
    } else {
        // TODO error - non-valid mode
    }

}

void SN_LoopControl::adjustRTC(char* dateParam) {
    tm tm1;
	sscanf(dateParam,"%4d.%2d.%2d %2d:%2d:%2d",&tm1.tm_year, &tm1.tm_mon,
            &tm1.tm_mday, &tm1.tm_hour, &tm1.tm_min, &tm1.tm_sec);

    clock.setRTCDateTime(DateTime(tm1.tm_year, tm1.tm_mon, tm1.tm_mday, tm1.tm_hour, tm1.tm_min, tm1.tm_sec));
}

boolean SN_LoopControl::isRTCLostPower() {
    return clock.isRTCLostPower();
}
