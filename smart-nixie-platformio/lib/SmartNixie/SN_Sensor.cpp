#include "SN_Sensor.h"

SN_Sensor::SN_Sensor() {
    // NOP
}

SN_Sensor::SN_Sensor(SN_Display *snDisp) {
    disp = snDisp;
    tempUnit = BME280::TempUnit(BME280::TempUnit_Celsius);
    presUnit = BME280::PresUnit(BME280::PresUnit_hPa);

    if (!bme.begin()) {
        Serial.println("ERROR - Could not find BME sensor.");
        // TODO: error handling
    }
}

void SN_Sensor::displayCurrentValues() {
    readValues();
    int t = round(temp);
    int h = round(hum);
    disp->showDec(h * 100 + t);
}

void SN_Sensor::readValues() {
    bme.read(pres, temp, hum, tempUnit, presUnit);
}

void SN_Sensor::testRead() {
    bme.read(pres, temp, hum, tempUnit, presUnit);

    Serial.println("-------------------------------");
    Serial.print("Temperature: ");
    Serial.println(temp);
    Serial.print("Humidity: ");
    Serial.println(hum);
    Serial.print("Pressure: ");
    Serial.println(pres);
}
