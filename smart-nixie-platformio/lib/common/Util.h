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
        static void printDebugLine(String param, boolean addNewLine = false);
        static void printDebugLine(String params[], int paramsSize, boolean addNewLine = false);

    private:
        const static boolean DEBUG = true;
        static RTC_DS3231 rtc;

};

#endif
