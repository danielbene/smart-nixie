#include "Display.h"

Display::Display(Adafruit_MCP23017 mcpObj) {
    mcp = mcpObj;

    mcp.begin(0);

    int minutePins[] = {4, 5, 6, 7};
    int hourPins[] = {11, 10, 9, 8};
    minutes = Tube(minutePins, mcp);
    hours = Tube(hourPins, mcp);
}

void Display::show(int num) {

    minutes.writeNum(num % 10);
    hours.writeNum((num % 100) / 10);
}
