#include "SN_LoopControl.h"

SN_LoopControl::SN_LoopControl() {
    // NOP
}

SN_LoopControl::SN_LoopControl(char *tzOffsetParam, char *manualDateTimeDateTimeParam, DateTime *cntUpStart, DateTime *cntDownEnd, boolean *isConn, Mode *modeParam) {
    clock = SN_Clock(&disp);
    sensor = SN_Sensor(&disp);

    tzOffset = tzOffsetParam;
    manualDateTime = manualDateTimeDateTimeParam;

    isConnected = isConn;
    countUpStart = cntUpStart;
    countDownEnd = cntDownEnd;

    mode = modeParam;
}

// this is the main logic node - displayed numbers gets decided here
void SN_LoopControl::doLoop() {

    if (*mode == SN_LoopControl::Mode::CLOCK) {
        clock.displayCurrentTime();
    } else if (*mode == SN_LoopControl::Mode::COUNTUP) {
        // TODO: add handling for >99:59 (low prior)
        clock.doCountUpLoop(countUpStart);
    } else if (*mode == SN_LoopControl::Mode::COUNTDOWN) {
        clock.doCountDownLoop(countDownEnd);
    } else if (*mode == SN_LoopControl::Mode::SENSOR) {
        sensor.displayCurrentValues();
    } else if (*mode == SN_LoopControl::Mode::ERROR) {
        // TODO error handling
        disp.flash(9999);
    } else if (*mode == SN_LoopControl::Mode::OFF) {
        disp.turnOff();
    }

    // ntp update will only do work if set update interval is reached so calling it often is fine
    if (*isConnected) {
        clock.getTimeClient()->update();
        Util::printDebugLine(clock.getTimeClient()->getFormattedTime(), true);
    }
}

void SN_LoopControl::timeParamUpdate() {
    if (strlen(tzOffset) != 0) {
        Util::printDebugLine("TIME PARAM UPDATE - NTP OFFSET", true);
        clock.setNTPOffset(atoi(tzOffset));
        clock.setRTCDateTime(clock.getTimeClient()->getEpochTime());
    } else if (strlen(manualDateTime) != 0) {
        Util::printDebugLine("TIME PARAM UPDATE - MANUAL DATETIME", true);
        clock.setRTCDateTime(Util::charToDateTime(manualDateTime));
    }

    resetTimeParams();
}

boolean SN_LoopControl::timeUpdate() {
    if (!clock.isRTCLostPower()){
        //we still have ~correct time in RTC
        //TODO: handling periodic ntp corrections outside
        Util::printDebugLine("FOUND RTC TIME", true);
    } else if (strlen(tzOffset) != 0) {
        clock.setNTPOffset(atoi(tzOffset));
        Util::printDebugLine("NO RTC TIME - SET NTP", true);
    } else if (strlen(manualDateTime) != 0) {
        clock.setRTCDateTime(Util::charToDateTime(manualDateTime));
        Util::printDebugLine("NO RTC TIME - SET MANUAL", true);
    } else {
        *mode = Mode::ERROR;
        Util::printDebugLine("NO RTC TIME - NO PARAMS - ERROR", true);
        return false;
    }

    *mode = Mode::CLOCK;
    resetTimeParams();
    
    Util::printDebugLine("TIME SET SUCCESSFULLY", true);
    return true;
}

void SN_LoopControl::resetTimeParams() {
    Util::printDebugLine("RESET TIME PARAMS", true);
    *tzOffset = (char) 0;
    *manualDateTime = (char) 0;
}
