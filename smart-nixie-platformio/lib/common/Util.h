#ifndef UTIL_H
#define UTIL_H

#include <Arduino.h>

class Util {
    public:
        static boolean isValidDate(const char* dateTime);
        static boolean isValidMacAddress(const char* mac);

};

#endif
