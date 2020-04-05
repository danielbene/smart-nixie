#ifndef SN_DISPLAY_H
#define SN_DISPLAY_H

#include <Arduino.h>
#include "Adafruit_MCP23017.h"
#include "SN_Tube.h"

class SN_Display {
    public:
        SN_Display();
        void show(int num);
        void flash(int num);    // ???
        void turnOff();

    private:
        Adafruit_MCP23017 mcp;
        SN_Tube minutes;
        SN_Tube tenMinutes;
        SN_Tube hours;
        SN_Tube tenHours;
        void setTubeValues(int tenHours, int hours, int tenMinutes, int minutes);

};

#endif
