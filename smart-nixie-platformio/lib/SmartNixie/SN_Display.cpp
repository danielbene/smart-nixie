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
    if (lastDisplayedDec != 0) {
        setTubeValues(0, 0, 0, 0);
    }

    setDisplayFlags(0, false);
}

void SN_Display::flash() {
    isFlashStateOn ? fillZeros() : turnOff();
    flashStateChange();
}

// TODO: this will be good for error codes too imo
void SN_Display::flash(int num) {
    isFlashStateOn ? showDec(num) : turnOff();
    flashStateChange();
}

void SN_Display::showDec(int num) {
    String msg[] = {String(num), "(", String(lastDisplayedDec), "): "};
    Util::printDebugLine(msg, 4);

    if (lastDisplayedDec != num) {
        setTubeValues((num % 10000) / 1000, (num % 1000) / 100, (num % 100) / 10, num % 10);
        setDisplayFlags(num, false);
    }

    Util::printDebugLine("", true);
}

void SN_Display::turnOff() {
    if (!isTurnedOff) {
        // undisplayable/invalid value turns off the tube - handled by the driver IC - RTFM
        setTubeValues(SN_Tube::INVALID_STATE, SN_Tube::INVALID_STATE, SN_Tube::INVALID_STATE, SN_Tube::INVALID_STATE);
        setDisplayFlags(-1, true);
    }
}

void SN_Display::flashStateChange() {
    if (millis() > lastFlashStateChange + FLASH_SPEED) {
        isFlashStateOn = !isFlashStateOn;
        lastFlashStateChange = millis();
    }
}

void SN_Display::setDisplayFlags(int displayNum, boolean isTOff) {
    lastDisplayedDec = displayNum;
    isTurnedOff = isTOff;
}

void SN_Display::setTubeValues(int tenHoursDec, int hoursDec, int tenMinutesDec, int minutesDec) {
    tenHoursTube.writeNum(tenHoursDec);
    hoursTube.writeNum(hoursDec);
    tenMinutesTube.writeNum(tenMinutesDec);
    minutesTube.writeNum(minutesDec);
}
