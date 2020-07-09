#include "SN_Clock.h"

SN_Clock::SN_Clock() {
    // NOP
}

SN_Clock::SN_Clock(SN_Display snDisp) {
    disp = snDisp;
    if (!rtc.begin()) {
        // TODO: error code - couldnt find RTC
    }
}

void SN_Clock::setRTCDateTime(DateTime currentDateTime) {
    rtc.adjust(currentDateTime);
}

void SN_Clock::setCountUp() {
    countUpStart = rtc.now();
}

void SN_Clock::setCountDown(int minutes) {
    // these conversions required because TimeSpan doesnt seems to handling big values very well (eg 14400 minutes)
    int days = minutes / 60 / 24;
    int hours = minutes / 60 % 24;
    minutes = minutes % 60;

    countDownEnd = rtc.now() + TimeSpan(days, hours, minutes, 0);
}

void SN_Clock::doCountDownLoop() {
    DateTime currentDateTime = rtc.now();
    TimeSpan current(currentDateTime.day(), currentDateTime.hour(), currentDateTime.minute(), currentDateTime.second());
    TimeSpan future(countDownEnd.day(), countDownEnd.hour(), countDownEnd.minute(), countDownEnd.second());

    TimeSpan diff = future - current;

    if (diff.totalseconds() > 0) {
        if (diff.days() == 0 && diff.hours() == 0) {
            displayTime(diff.minutes() * 100 + diff.seconds());
        } else {
            displayTime(diff.hours() * 100 + diff.minutes());
        }
    } else {
        disp.flash();
    }
}

void SN_Clock::displayCurrentTime() {
    displayTime(getCurrentTimeAsDec());
}

void SN_Clock::testClock() {
    DateTime now = rtc.now();

    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print("   ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
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
    Serial.println();
    Serial.println("-------------------------------");
    disp.showDec(decTime);
}
