#ifndef SN_TUBE_H
#define SN_TUBE_H

#include <Arduino.h>
#include "Adafruit_MCP23017.h"

class SN_Tube {
    public:
        SN_Tube();
        SN_Tube(int ioPins[], Adafruit_MCP23017 mcpObj);
        void writeNum(int num);
    private:
        Adafruit_MCP23017 mcp;
        int ioPins[4]; // pin numbers on the io expander: [0] - represents binary 8; [3] - represents binary 0-1
};

#endif
