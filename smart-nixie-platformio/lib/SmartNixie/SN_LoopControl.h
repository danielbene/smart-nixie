#ifndef SN_LOOPCONTROL_H
#define SN_LOOPCONTROL_H

#include <Arduino.h>
#include "SN_Clock.h"
#include "SN_Display.h"
#include "SN_Sensor.h"

class SN_LoopControl {
    public:
        SN_LoopControl();
        enum class Mode {CLOCK, COUNTDOWN, COUNTUP, ERROR, SENSOR, OFF};
		void doLoop(SN_LoopControl::Mode mode);
        void adjustRTC(char* dateParam);
        boolean isRTCLostPower();

    private:
        SN_Clock clock;
        SN_Display disp;
        SN_Sensor sensor;

};

#endif
