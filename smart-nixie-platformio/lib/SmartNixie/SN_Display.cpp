#include "SN_Display.h"

Adafruit_MCP23017 mcp;

SN_Display::SN_Display() {
    // address 0 is set by the mcp23017 wiring - RTFM
    mcp.begin(0);

    // TODO: cleaner setup?
    int minutePins[] = {4, 5, 6, 7};
    int tenMinutePins[] = {0, 1, 2, 3};
    int hourPins[] = {11, 10, 9, 8};
    int tenHourPins[] = {15, 14, 13, 12};

    minutes = SN_Tube(minutePins, mcp);
    tenMinutes = SN_Tube(tenMinutePins, mcp);
    hours = SN_Tube(hourPins, mcp);
    tenHours = SN_Tube(tenHourPins, mcp);
}

void SN_Display::show(int num) {
    // TODO: explode, or split function instead of this
    minutes.writeNum(num % 10);
    tenMinutes.writeNum((num % 100) / 10);
    hours.writeNum((num % 1000) / 100);
    tenHours.writeNum((num % 10000) / 1000);

    /* working example with potmeter adjusted nixie values
    value = map(analogRead(A0), 0, 1023, 0, 99);
    disp.show(value);
    delay(150);*/
}
