#include "SN_Clock.h"

DateTime defaultDateTime(2000, 1, 1, 0, 0, 0);

SN_Clock::SN_Clock() {
    if (!rtc.begin()) {
        // TODO: error code - couldnt find RTC
    }

    if (rtc.lostPower) {
        setTime(defaultDateTime);   // this only happens if rtc module battery dies, or get removed
    }
}

void SN_Clock::setTime(DateTime currentDateTime) {
    rtc.adjust(currentDateTime);
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

int SN_Clock::getCurrentTimeAsDec() {
    DateTime now = rtc.now();
    return now.hour * 100 + now.minute;
}

void SN_Clock::displayTime(int decTime) {
    disp.show(decTime);
}
