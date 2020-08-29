#include "SN_Sensor.h"

SN_Sensor::SN_Sensor() {
    // NOP
}

SN_Sensor::SN_Sensor(SN_Display *snDisp) {
    disp = snDisp;
    tempUnit = BME280::TempUnit(BME280::TempUnit_Celsius);
    presUnit = BME280::PresUnit(BME280::PresUnit_hPa);

    if (!bme.begin()) {
        Util::printDebugLine("ERROR - Could not find BME sensor.", true);
        // TODO: error handling
    }
}

void SN_Sensor::displayCurrentValues() {
    readValues();
    int t = round(temp);
    int h = round(hum);
    disp->showDec(h * 100 + t, false);
}

void SN_Sensor::readValues() {
    bme.read(pres, temp, hum, tempUnit, presUnit);
}
