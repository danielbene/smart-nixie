#ifndef UTIL_H
#define UTIL_H

#include <Arduino.h>
#include <RTClib.h>

class Util {
    public:
        const static int16_t MAX_DISPLAYABLE_SECS = 5999; // total seconds for the "max displayable time in MINUTES without scaling" -> 99:59
        static boolean isValidDate(const char* dateTime);
        static boolean isValidMacAddress(const char* mac);
        static DateTime calculateFutureTime(int32_t minutes);

    private:
        static RTC_DS3231 rtc;

};

#endif
