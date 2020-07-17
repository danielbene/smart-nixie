#ifndef SN_CLOCK_H
#define SN_CLOCK_H

#include <Arduino.h>
#include <RTClib.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#include "config.h"
#include "SN_Display.h"
#include "Util.h"

static WiFiUDP ntpUDP;
static NTPClient timeClient(ntpUDP, NTP_SERVER, 0, NTP_UPDATE_MS);

class SN_Clock {
    public:
        SN_Clock();
        SN_Clock(SN_Display *snDisp);
        void displayCurrentTime();
        void doCountDownLoop(DateTime *countDownEnd);
        void doCountUpLoop(DateTime *countUpStart);
        void setNTPOffset(int hours);
        void setRTCDateTime(DateTime currentDateTime);
        boolean isRTCLostPower();
        DateTime getCurrentDateTime();
        NTPClient *getTimeClient();

    private:
        SN_Display *disp;
        RTC_DS3231 rtc;
        int getCurrentTimeAsDec();
        void displayTime(int decTime);

};

#endif
