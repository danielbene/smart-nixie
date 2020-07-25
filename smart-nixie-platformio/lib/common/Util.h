#ifndef UTIL_H
#define UTIL_H

#include <Arduino.h>
#include <RTClib.h>

class Util {
    public:
        static boolean isValidDate(const char *dateTime);
        static boolean isValidMacAddress(const char *mac);
        static DateTime calculateFutureTime(int32_t minutes);
        static DateTime charToDateTime(char *dateTimeStr);
        static DateTime charToTime(char *timeStr);
        static void printDebugLine(String param, boolean addNewLine = false);
        static void printDebugLine(String params[], int paramsSize, boolean addNewLine = false);

    private:
        static RTC_DS3231 rtc;

};

#endif
