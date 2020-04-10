#ifndef SN_DISPLAY_H
#define SN_DISPLAY_H

#include <Arduino.h>
#include "Adafruit_MCP23017.h"
#include "SN_Tube.h"

#define FLASH_SPEED 1000L

class SN_Display {
    public:
        SN_Display();
        void fillZeros();
        void flash();
        void flash(int num);
        void showDec(int num);
        void turnOff();

    private:
        boolean isFlashStateOn = true;
        boolean isTurnedOff;
        int lastDisplayedDec = 0;
        unsigned long lastFlashStateChange = millis();
        Adafruit_MCP23017 mcp;
        SN_Tube tenHoursTube;
        SN_Tube hoursTube;
        SN_Tube tenMinutesTube;
        SN_Tube minutesTube;
        void flashStateChange();
        void setDisplayFlags(int displayNum, boolean isTurnedOff);
        void setTubeValues(int tenHoursDec, int hoursDec, int tenMinutesDec, int minutesDec);

};

#endif
