#include "Tube.h"

Tube::Tube(int pins[4], Adafruit_MCP23017 mcpObj) {
    mcp = mcpObj;
    for (int i = 0; i < 4; i++) {
        ioPins[i] = pins[i];
        pinMode(ioPins[i], OUTPUT);
    }
}

void writeNum(int num) {
    int binaryNum[4]; 

    int i = 0; 
    while (num > 0) { 
        binaryNum[i] = num % 2; 
        num = num / 2; 
        i++; 
    }

    for (int i = 0; i < 4; i++) {
        //digitalWrite(ioPins[i], binaryNum[i]);
        mcp.digitalWrite(ioPins[i], binaryNum[i]);
    }
}