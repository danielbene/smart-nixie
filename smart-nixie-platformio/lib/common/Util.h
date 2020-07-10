#ifndef UTIL_H
#define UTIL_H

#include <Arduino.h>

class Util {
    public:
        const static int16_t MAX_DISPLAYABLE_SECS = 5999; // total seconds for the "max displayable time in MINUTES without scaling" -> 99:59
        static boolean isValidDate(const char* dateTime);
        static boolean isValidMacAddress(const char* mac);

};

#endif
