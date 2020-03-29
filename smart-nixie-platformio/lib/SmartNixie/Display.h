#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include "Adafruit_MCP23017.h"
#include "Tube.h"

class Display {
    public:
        Display(Adafruit_MCP23017 mcpObj);
        void show(int num);
    private:
        Adafruit_MCP23017 mcp;
        Tube minutes;
        Tube hours;
};

#endif
