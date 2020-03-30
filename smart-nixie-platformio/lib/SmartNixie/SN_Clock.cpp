#include "SN_Clock.h"

SN_Clock::SN_Clock() {
    if (!rtc.begin()) {
        // TODO: error code - couldnt find RTC
    }

    // TODO: current time management
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

// for testing
void SN_Clock::serialClock() {
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
