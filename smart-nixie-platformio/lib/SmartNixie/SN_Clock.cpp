#include "SN_Clock.h"

SN_Clock::SN_Clock() {
    // NOP
}

SN_Clock::SN_Clock(SN_Display *snDisp) {
    disp = snDisp;
    if (!rtc.begin()) {
        // TODO: error code - couldnt find RTC
    }

    setupNtpClient();
}

void SN_Clock::setRTCDateTime(DateTime currentDateTime) {
    rtc.adjust(currentDateTime);
}

void SN_Clock::setupNtpClient() {
    // default update interval is 4 hours (=14400000ms)
    // 0 minute offset (its for timezone hours?)
    // in theory pool.ntp.org will find the closest server, so timezone setup not needed
    *timeClient = NTPClient(ntpUDP, "europe.pool.ntp.org", 0, 14400000);
    timeClient->begin();

    // FIXME: calling timeClient causes exception!!!

    // TODO: implement NTP usage based on this repo (https://github.com/arduino-libraries/NTPClient)
    // https://www.pool.ntp.org/zone/europe
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

    if (diff.totalseconds() <= Util::MAX_DISPLAYABLE_SECS) {
        displayTime(diff.minutes() * 100 + diff.seconds());
    } else {
        disp->flash(9959);
    }
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

int SN_Clock::getCurrentTimeAsDec() {
    DateTime now = rtc.now();
    return now.hour() * 100 + now.minute();
}

void SN_Clock::displayTime(int decTime) {
    Util::printDebugLine("-------------------------------", true);
    disp->showDec(decTime);
}
