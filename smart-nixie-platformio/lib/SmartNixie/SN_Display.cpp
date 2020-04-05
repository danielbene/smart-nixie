#include "SN_Display.h"

Adafruit_MCP23017 mcp;

SN_Display::SN_Display() {
    mcp.begin(0);   // address 0 is set by the mcp23017 wiring - RTFM

    // these are the Adafruit pin addresses of the mcp for the tube driver controlls
    int ioPins[4][4] = {{4, 5, 6, 7}, {0, 1, 2, 3}, {11, 10, 9, 8}, {15, 14, 13, 12}};

    minutes = SN_Tube(ioPins[0], mcp);
    tenMinutes = SN_Tube(ioPins[1], mcp);
    hours = SN_Tube(ioPins[2], mcp);
    tenHours = SN_Tube(ioPins[3], mcp);
}

void SN_Display::show(int num) {
    Serial.print(num);
    Serial.print(": ");

    setTubeValues((num % 10000) / 1000, (num % 1000) / 100, (num % 100) / 10, num % 10);
}

void SN_Display::turnOff() {
    // undisplayable value turns off the tube - handled by the driver IC
    setTubeValues(10, 10, 10, 10);
}

void SN_Display::setTubeValues(int tenHoursDec, int hoursDec, int tenMinutesDec, int minutesDec) {
    tenHours.writeNum(tenHoursDec);
    hours.writeNum(hoursDec);
    tenMinutes.writeNum(tenMinutesDec);
    minutes.writeNum(minutesDec);
}
