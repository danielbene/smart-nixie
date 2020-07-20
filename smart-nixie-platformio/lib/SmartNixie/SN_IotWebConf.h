#ifndef SN_IOTWEBCONF_H
#define SN_IOTWEBCONF_H

#include <Arduino.h>
#include <ESP8266mDNS.h>
#include <ESP8266WiFiMulti.h>
#include <IotWebConf.h>
#include <RTClib.h>

#include "SN_LoopControl.h"
#include "Util.h"

#define CONFIG_VERSION "asd2"
#define CONFIG_PIN D5
#define STATUS_PIN LED_BUILTIN

#define STRING_LEN 128
#define NUMBER_LEN 32

const char thingName[] = "smart-nixie";
const char wifiInitialApPassword[] = "12345678";
static DNSServer dnsServer;
static ESP8266WebServer server(80);

static IotWebConf iotWebConf(thingName, &dnsServer, &server, wifiInitialApPassword);

static char dateTimeParamValue[STRING_LEN];
static char tzOffsetHours[3];
static IotWebConfSeparator timeSeparator = IotWebConfSeparator("Manual/Auto time settings");
static IotWebConfParameter dateTimeParam = IotWebConfParameter("Current time for manual setup", "dateTimeParam", dateTimeParamValue, STRING_LEN, "text", "2020.01.01 11:00:00", "");

//TODO: add offset field validation
static IotWebConfParameter tzidParam = IotWebConfParameter("Timezone offset from UTC in hours", "tzOffset", tzOffsetHours, 3, "text", "-1", "");

class SN_IotWebConf {
    public:
        SN_IotWebConf();
        SN_IotWebConf(SN_LoopControl::Mode *mode, DateTime *cntUpStart, DateTime *cntDownEnd);
        static boolean isConnected;
		void setup();
		void doLoop();
        char *getDateTimeParam();
        char *getTZOffsetParam();

    private:
        static SN_LoopControl::Mode *currentMode;
        static DateTime *countUpStart;
        static DateTime *countDownEnd;
        static boolean formValidator();
        static void onConfigSaved();
        static void onConnect();
        static void handleRoot();
        static void onClockState();
        static void onCountUpState();
        static void onCountDownState();
        static void onSensorState();
        static void onOffState();
        static RTC_DS3231 rtc;

};

#endif
