#include "SN_Tube.h"

SN_Tube::SN_Tube() {
    // NOP
}

SN_Tube::SN_Tube(int pins[4], Adafruit_MCP23017 mcpObj) {
    mcp = mcpObj;
    for (int i = 0; i < 4; i++) {
        ioPins[i] = pins[i];
        mcp.pinMode(ioPins[i], OUTPUT);
        mcp.pullUp(ioPins[i], true);
    }
}

void SN_Tube::writeNum(int num) {
    int binaryNum[4] = {0, 0, 0, 0};
    int i = 3;

    while (num > 0) {
        binaryNum[i] = num % 2;
        num = num / 2;
        i--;
    }

    for (int i = 0; i < 4; i++) {
        Util::printDebugLine(String(binaryNum[i]));
        mcp.digitalWrite(ioPins[i], binaryNum[i]);
    }

    Util::printDebugLine("  ");
}
