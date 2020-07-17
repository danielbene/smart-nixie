#ifndef SN_LOOPCONTROL_H
#define SN_LOOPCONTROL_H

#include <Arduino.h>
#include "SN_Clock.h"
#include "SN_Display.h"
#include "SN_Sensor.h"

class SN_LoopControl {
    public:
        SN_LoopControl();
        SN_LoopControl(DateTime *cntUpStart, DateTime *cntDownEnd, boolean *isConnected);
        enum class Mode {CLOCK, COUNTDOWN, COUNTUP, ERROR, SENSOR, OFF};
		void doLoop(SN_LoopControl::Mode mode);
        boolean timeUpdate(boolean *isTimeParamsUpdated, boolean isNtpTime, char *tzOffset, char *manualDateTime);

    private:
        SN_Clock clock;
        SN_Display disp;
        SN_Sensor sensor;
        boolean isNTPTime;
        boolean *isConnected;
        DateTime *countUpStart;
        DateTime *countDownEnd;

};

#endif
