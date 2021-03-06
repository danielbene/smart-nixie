#include "SN_LoopControl.h"

SN_LoopControl::SN_LoopControl() {
    // NOP
}

SN_LoopControl::SN_LoopControl(char *tzOffsetParam, char *manualDateTimeDateTimeParam, char *slotmachineTimeParam, char *blankingLeftZeros, DateTime *cntUpStart, DateTime *cntDownEnd, boolean *isConn, Mode *modeParam) {
    clock = SN_Clock(&disp);
    sensor = SN_Sensor(&disp);

    clock.blankLeftZeros = blankingLeftZeros;

    tzOffset = tzOffsetParam;
    manualDateTime = manualDateTimeDateTimeParam;
    slotmachineTime = slotmachineTimeParam;

    isConnected = isConn;
    countUpStart = cntUpStart;
    countDownEnd = cntDownEnd;

    mode = modeParam;
}

// this is the main logic node - displayed numbers gets decided here
void SN_LoopControl::doLoop() {

    if (*mode == Mode::CLOCK) {
        clock.displayCurrentTime();
        slotmachineCheck();
    } else if (*mode == Mode::COUNTUP) {
        // TODO: add handling for >99:59 (low prior)
        clock.doCountUpLoop(countUpStart);
    } else if (*mode == Mode::COUNTDOWN) {
        clock.doCountDownLoop(countDownEnd);
    } else if (*mode == Mode::SENSOR) {
        sensor.displayCurrentValues();
    } else if (*mode == Mode::SLOTMACHINE && clock.doSlotmachineLoop(&slotmachineStart)) {
        *mode = Mode::CLOCK;
    } else if (*mode == Mode::ERROR) {
        // TODO error handling
        disp.flash(9999);
    } else if (*mode == Mode::OFF) {
        disp.turnOff();
    }

    // ntp update will only do work if set update interval is reached so calling it often is fine
    if (*isConnected) {
        //TODO: remove if periodic update not available
        clock.getTimeClient()->update();
        Util::printDebugLine(clock.getTimeClient()->getFormattedTime(), true);
    }
}

void SN_LoopControl::timeParamUpdate() {

    //TODO: NTP update, and periodic correction may not be useful with the current aproach
    //after a poweroff it cannot be decided if the stored time is based on NTP because of the
    //iotwebconf tzOffset param reset - EEPROM stored flag may solve this

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
        //NOP - time setup is fine / may gets logic later
    } else if (strlen(tzOffset) != 0) {
        clock.setNTPOffset(atoi(tzOffset));
    } else if (strlen(manualDateTime) != 0) {
        clock.setRTCDateTime(Util::charToDateTime(manualDateTime));
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
    Util::printDebugLine("RESET IOTWEBCONF TIME PARAMS", true);
    *tzOffset = (char) 0;
    *manualDateTime = (char) 0;
}

void SN_LoopControl::slotmachineCheck() {
    //this is called only if clock mode active
    DateTime now = clock.getCurrentDateTime();
    DateTime slotmachineDT = Util::charToTime(slotmachineTime); //TODO: refactor -> parsing only when config changes 
    if (slotmachineDT.hour() == now.hour() && slotmachineDT.minute() == now.minute()) {
        Util::printDebugLine("ITS SLOTMACHINE TIME", true);
        *mode = Mode::SLOTMACHINE;
        slotmachineStart = now;
    }
}
