#ifndef SN_CLOCK_H
#define SN_CLOCK_H

#include <Arduino.h>
#include "SN_Display.h"
#include "RTClib.h"

class SN_Clock {
    public:
        SN_Clock();
        SN_Display disp;
        RTC_DS3231 rtc;
        void displayCurrentTime();
        void doCountDownLoop();
        void setCountUp();
        void setCountDown(int minutes);
        void setRTCDateTime(DateTime currentDateTime);
        void testClock();

    private:
        int getCurrentTimeAsDec();
        void displayTime(int decTime);

};

#endif
