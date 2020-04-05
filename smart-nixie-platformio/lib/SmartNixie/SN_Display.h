#ifndef SN_DISPLAY_H
#define SN_DISPLAY_H

#include <Arduino.h>
#include "Adafruit_MCP23017.h"
#include "SN_Tube.h"

class SN_Display {
    public:
        SN_Display();
        boolean isFlashStateOn = true;
        boolean isTurnedOff;
        void fillZeros();
        void flash();
        void flash(int num);
        void showDec(int num);
        void turnOff();

    private:
        Adafruit_MCP23017 mcp;
        SN_Tube tenHoursTube;
        SN_Tube hoursTube;
        SN_Tube tenMinutesTube;
        SN_Tube minutesTube;
        void setTubeValues(int tenHoursDec, int hoursDec, int tenMinutesDec, int minutesDec);

};

#endif
