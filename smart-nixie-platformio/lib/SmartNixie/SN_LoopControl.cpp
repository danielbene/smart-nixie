#include "SN_LoopControl.h"

SN_LoopControl::SN_LoopControl() {
    // NOP
}

SN_LoopControl::SN_LoopControl(DateTime *cntUpStart, DateTime *cntDownEnd, boolean *isConn) {
    clock = SN_Clock(&disp);
    sensor = SN_Sensor(&disp);

    isConnected = isConn;
    countUpStart = cntUpStart;
    countDownEnd = cntDownEnd;
}

// this is the main logic node - displayed numbers gets decided here
void SN_LoopControl::doLoop(SN_LoopControl::Mode mode) {

    if (mode == SN_LoopControl::Mode::CLOCK) {
        clock.displayCurrentTime();
    } else if (mode == SN_LoopControl::Mode::COUNTUP) {
        // TODO: add handling for >99:59 (low prior)
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
    }

    // ntp update will only do work if set update interval is reached so calling it often is fine
    //if (isConnected && isNTPTime) clock.timeClient->update();
    if (*isConnected) {
        clock.getTimeClient()->update();
        Util::printDebugLine(clock.getTimeClient()->getFormattedTime(), true);
    }
}

boolean SN_LoopControl::timeUpdate(boolean *isTimeParamsUpdated, boolean isNtp, char *manualDateTime) {

    isNTPTime = isNtp;

    if (isTimeParamsUpdated) {
        if (isNTPTime) {
            // TODO: web based time setup
            //clock.setRTCDateTime(DateTime(clock.timeClient->getEpochTime()));
            Util::printDebugLine("NTP TIME SELECTED?!", true);
        } else {
            clock.setRTCDateTime(Util::charToDateTime(manualDateTime));
        }

        clock.setRTCDateTime(Util::charToDateTime(manualDateTime));

        *isTimeParamsUpdated = false;
        return true;
    }

    return !clock.isRTCLostPower();
}
