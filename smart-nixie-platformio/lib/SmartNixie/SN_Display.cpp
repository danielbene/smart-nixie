#include "SN_Display.h"

Adafruit_MCP23017 mcp;

SN_Display::SN_Display() {
    mcp.begin(0);   // address 0 is set by the mcp23017 wiring - RTFM

    // these are the Adafruit pin addresses of the mcp for the tube driver controlls
    int ioPins[4][4] = {{15, 14, 13, 12}, {11, 10, 9, 8}, {0, 1, 2, 3}, {4, 5, 6, 7}};

    tenHoursTube = SN_Tube(ioPins[0], mcp);
    hoursTube = SN_Tube(ioPins[1], mcp);
    tenMinutesTube = SN_Tube(ioPins[2], mcp);
    minutesTube = SN_Tube(ioPins[3], mcp);
}

void SN_Display::fillZeros() {
    setTubeValues(0, 0, 0, 0);
    isTurnedOff = false;
}

// TODO: flashing speed is controlled by the calls (so basically the DELAY timer) - is it too fast?
void SN_Display::flash() {
    isFlashStateOn ? fillZeros() : turnOff();
    isFlashStateOn = !isFlashStateOn;
}

// TODO: this will be good for error codes too imo
void SN_Display::flash(int num) {
    isFlashStateOn ? showDec(num) : turnOff();
    isFlashStateOn = !isFlashStateOn;
}

void SN_Display::showDec(int num) {
    Serial.print(num);
    Serial.print(": ");

    setTubeValues((num % 10000) / 1000, (num % 1000) / 100, (num % 100) / 10, num % 10);
    isTurnedOff = false;
}

void SN_Display::turnOff() {
    if (!isTurnedOff) {
        // undisplayable/invalid value turns off the tube - handled by the driver IC - RTFM
        setTubeValues(SN_Tube::INVALID_STATE, SN_Tube::INVALID_STATE, SN_Tube::INVALID_STATE, SN_Tube::INVALID_STATE);
        isTurnedOff = true;
    }
}

void SN_Display::setTubeValues(int tenHoursDec, int hoursDec, int tenMinutesDec, int minutesDec) {
    tenHoursTube.writeNum(tenHoursDec);
    hoursTube.writeNum(hoursDec);
    tenMinutesTube.writeNum(tenMinutesDec);
    minutesTube.writeNum(minutesDec);
}
