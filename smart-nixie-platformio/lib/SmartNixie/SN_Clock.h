#ifndef SN_CLOCK_H
#define SN_CLOCK_H

#include <Arduino.h>
#include <RTClib.h>
#include "SN_Display.h"

class SN_Clock {
    public:
        SN_Clock();
        SN_Clock(SN_Display snDisp);
        void displayCurrentTime();
        void doCountDownLoop();
        void setCountUp();
        void setCountDown(int minutes);
        void setRTCDateTime(DateTime currentDateTime);
        void testClock();

    private:
        DateTime defaultDateTime;
        DateTime countUpStart;
        DateTime countDownEnd;
        SN_Display disp;
        RTC_DS3231 rtc;
        int getCurrentTimeAsDec();
        void displayTime(int decTime);

};

#endif
