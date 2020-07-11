#include "SN_LoopControl.h"

SN_LoopControl::SN_LoopControl() {
    clock = SN_Clock(&disp);
    sensor = SN_Sensor(&disp);
}

SN_LoopControl::SN_LoopControl(DateTime *cntUpStart, DateTime *cntDownEnd) {
    clock = SN_Clock(&disp);
    sensor = SN_Sensor(&disp);

    countUpStart = cntUpStart;
    countDownEnd = cntDownEnd;
}

// this is the main logic node - displayed numbers gets decided here
void SN_LoopControl::doLoop(SN_LoopControl::Mode mode) {

    if (mode == SN_LoopControl::Mode::CLOCK) {
        clock.displayCurrentTime();
    } else if (mode == SN_LoopControl::Mode::COUNTUP) {
        // TODO: add handling for >99:59
        clock.doCountUpLoop(countUpStart);
    } else if (mode == SN_LoopControl::Mode::COUNTDOWN) {
        clock.doCountDownLoop(countDownEnd);
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
