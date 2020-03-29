#ifndef TUBE_H
#define TUBE_H

#include <Arduino.h>
#include "Adafruit_MCP23017.h"

class Tube {
    public:
        Tube();
        Tube(int ioPins[], Adafruit_MCP23017 mcpObj);
        void writeNum(int num); // num has to be < 10
    private:
        Adafruit_MCP23017 mcp;
        int ioPins[4]; // pin numbers on the io expander: [0] - represents binary 8; [3] - represents binary 0-1
};

#endif
