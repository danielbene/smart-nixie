#include "SN_Clock.h"

SN_Clock::SN_Clock() {
    // NOP
}

SN_Clock::SN_Clock(SN_Display *snDisp) {
    disp = snDisp;
    if (!rtc.begin()) {
        // TODO: error code - couldnt find RTC
    }

    timeClient.begin();
}

void SN_Clock::setRTCDateTime(DateTime currentDateTime) {
    rtc.adjust(currentDateTime);
}

void SN_Clock::doCountDownLoop(DateTime *countDownEnd) {
    DateTime currentDateTime = rtc.now();
    TimeSpan current(currentDateTime.day(), currentDateTime.hour(), currentDateTime.minute(), currentDateTime.second());
    TimeSpan future((*countDownEnd).day(), (*countDownEnd).hour(), (*countDownEnd).minute(), (*countDownEnd).second());

    TimeSpan diff = future - current;

    if (diff.totalseconds() > 0) {
        if (diff.days() == 0 && diff.hours() == 0) {
            displayTime(diff.minutes() * 100 + diff.seconds());
        } else {
            displayTime(diff.hours() * 100 + diff.minutes());
        }
    } else {
        disp->flash();
    }
}

void SN_Clock::doCountUpLoop(DateTime *countUpStart) {
    DateTime currentDateTime = rtc.now();
    TimeSpan current(currentDateTime.day(), currentDateTime.hour(), currentDateTime.minute(), currentDateTime.second());
    TimeSpan start((*countUpStart).day(), (*countUpStart).hour(), (*countUpStart).minute(), (*countUpStart).second());

    TimeSpan diff = current - start;

    if (diff.totalseconds() <= SN_MAX_DISPLAYABLE_SECS) {
        displayTime(diff.minutes() * 100 + diff.seconds());
    } else {
        disp->flash(9959);
    }
}

boolean SN_Clock::doSlotmachineLoop(DateTime *slotmachineStart) {
    //TODO: refact these TimeSpans
    DateTime currentDateTime = rtc.now();
    TimeSpan current(currentDateTime.day(), currentDateTime.hour(), currentDateTime.minute(), currentDateTime.second());
    TimeSpan start((*slotmachineStart).day(), (*slotmachineStart).hour(), (*slotmachineStart).minute(), (*slotmachineStart).second());

    TimeSpan diff = current - start;

    if (diff.totalseconds() > 100) {
        return true;
    } else if (diff.totalseconds() < 10) {
        disp->fillZeros();
    } else {
        int cycle = (int)diff.totalseconds() / 10;
        int cathodeNums = cycle * 1000 + cycle * 100 + cycle * 10 + cycle;

        disp->showDec(cathodeNums, false);
    }

    return false;
}

// set the timezone of the NTP updates (UTC +-hours)
void SN_Clock::setNTPOffset(int hours) {
    timeClient.setTimeOffset(hours * 3600);
}

void SN_Clock::displayCurrentTime() {
    displayTime(getCurrentTimeAsDec());
}

boolean SN_Clock::isRTCLostPower() {
    return rtc.lostPower(); // this only happens if rtc module battery dies, or get removed
}

DateTime SN_Clock::getCurrentDateTime() {
    return rtc.now();
}

NTPClient *SN_Clock::getTimeClient() {
    return &timeClient;
}

int SN_Clock::getCurrentTimeAsDec() {
    DateTime now = rtc.now();
    return now.hour() * 100 + now.minute();
}

void SN_Clock::displayTime(int decTime) {
    Util::printDebugLine("-------------------------------", true);
    disp->showDec(decTime, true);
}
