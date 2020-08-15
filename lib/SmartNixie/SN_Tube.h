#ifndef SN_TUBE_H
#define SN_TUBE_H

#include <Adafruit_MCP23017.h>
#include <Arduino.h>

#include "Util.h"

class SN_Tube {
    public:
        SN_Tube();
        SN_Tube(int ioPins[], Adafruit_MCP23017 mcpObj);
        static const int INVALID_STATE = 12;
        void writeNum(int num);
    private:
        Adafruit_MCP23017 mcp;
        int ioPins[4];  // pin numbers on the io expander: [0] - represents dec 8; [3] - represents dec 1
};

#endif
