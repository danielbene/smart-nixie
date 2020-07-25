#ifndef SN_LOOPCONTROL_H
#define SN_LOOPCONTROL_H

#include <Arduino.h>

#include "SN_Clock.h"
#include "SN_Display.h"
#include "SN_Sensor.h"

class SN_LoopControl {
    public:
        enum class Mode {CLOCK, COUNTDOWN, COUNTUP, ERROR, SENSOR, SLOTMACHINE, OFF};
        SN_LoopControl();
        SN_LoopControl(char *tzOffset, char *manualDateTime, DateTime *cntUpStart, DateTime *cntDownEnd, boolean *isConnected, Mode *mode);
		void doLoop();
        void timeParamUpdate();
        boolean timeUpdate();

    private:
        char *manualDateTime;
        char *tzOffset;
        Mode *mode;
        void resetTimeParams();
        void slotmachineCheck();
        SN_Clock clock;
        SN_Display disp;
        SN_Sensor sensor;
        boolean *isConnected;
        DateTime *countUpStart;
        DateTime *countDownEnd;
        DateTime slotmachineStart;

};

#endif
