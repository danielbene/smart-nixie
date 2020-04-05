#include "SN_Clock.h"

DateTime defaultDateTime(2000, 1, 1, 0, 0, 0);
DateTime countUpStart;
DateTime countDownEnd;

SN_Clock::SN_Clock() {
    if (!rtc.begin()) {
        // TODO: error code - couldnt find RTC
    }

    if (rtc.lostPower()) {
        setRTCDateTime(defaultDateTime);   // this only happens if rtc module battery dies, or get removed
    }
}

void SN_Clock::setRTCDateTime(DateTime currentDateTime) {
    rtc.adjust(currentDateTime);
}

void SN_Clock::setCountUp() {
    countUpStart = rtc.now();
}

void SN_Clock::setCountDown(int minutes) {
    //DateTime currentDateTime = rtc.now();

    // these conversions required because TimeSpan doesnt seems to handling big values very well (eg 14400 minutes)
    int days = minutes / 60 / 24;
    int hours = minutes / 60 % 24;
    minutes = minutes % 60;

    countDownEnd = rtc.now() + TimeSpan(days, hours, minutes, 0);

    /*Serial.println("#################################");
    Serial.print("Current time: ");
    Serial.print(currentDateTime.month());
    Serial.print("/");
    Serial.print(currentDateTime.day());
    Serial.print("  ");
    Serial.print(currentDateTime.hour());
    Serial.print(":");
    Serial.println(currentDateTime.minute());
    Serial.print("Future time: ");
    Serial.print(countDownEnd.month());
    Serial.print("/");
    Serial.print(countDownEnd.day());
    Serial.print("  ");
    Serial.print(countDownEnd.hour());
    Serial.print(":");
    Serial.println(countDownEnd.minute());*/
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
        // TODO: timer end - flashing display?
        Serial.println("TIMES UP!");
    }

    /*Serial.println("----------------------");
    Serial.println(diff.totalseconds());
    Serial.print(diff.days());
    Serial.print(" | ");
    Serial.print(diff.hours());
    Serial.print(":");
    Serial.print(diff.minutes());
    Serial.print(":");
    Serial.print(diff.seconds());
    Serial.println();*/
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
    return now.hour() * 100 + now.minute();
}

void SN_Clock::displayTime(int decTime) {
    Serial.println();
    Serial.println("-------------------------------");
    disp.show(decTime);
}
