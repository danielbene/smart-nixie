#ifndef SN_SENSOR_H
#define SN_SENSOR_H

#include <Arduino.h>
#include <BME280I2C.h>

#include "SN_Display.h"
#include "Util.h"

class SN_Sensor {
    public:
        SN_Sensor();
        SN_Sensor(SN_Display *snDisp);
        BME280I2C bme;
        void displayCurrentValues();

    private:
        BME280::TempUnit tempUnit;
        BME280::PresUnit presUnit;
        SN_Display *disp;
        float temp;
        float hum;
        float pres;
        void readValues();

};

#endif
