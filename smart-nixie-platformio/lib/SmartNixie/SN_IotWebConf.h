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
const char wifiInitialApPassword[] = "123456";
static DNSServer dnsServer;
static ESP8266WebServer server(80);

static IotWebConf iotWebConf(thingName, &dnsServer, &server, wifiInitialApPassword);

static char dateTimeParamValue[STRING_LEN];
static char tzidParamValue[STRING_LEN];
//static char mac1ParamValue[STRING_LEN];
//static char mac2ParamValue[STRING_LEN];
//static char mac3ParamValue[STRING_LEN];
static IotWebConfSeparator timeSeparator = IotWebConfSeparator("Manual/Auto time settings");
static IotWebConfParameter dateTimeParam = IotWebConfParameter("Current time for manual setup", "dateTimeParam", dateTimeParamValue, STRING_LEN, "text", "2020.12.25 13:30:25", "");
static IotWebConfParameter tzidParam = IotWebConfParameter("Timezone for automatic setup", "tzidParam", tzidParamValue, STRING_LEN, "text", "Europe/Budapest", "");
//static IotWebConfSeparator turnoffSeparator = IotWebConfSeparator("Auto turnoff settings");
//static IotWebConfParameter mac1Param = IotWebConfParameter("Device 1 MAC address", "mac1Param", mac1ParamValue, STRING_LEN, "text", "12:34:56:78:9A:BC", "");
//static IotWebConfParameter mac2Param = IotWebConfParameter("Device 2 MAC address", "mac2Param", mac2ParamValue, STRING_LEN, "text", "12:34:56:78:9A:BC", "");
//static IotWebConfParameter mac3Param = IotWebConfParameter("Device 3 MAC address", "mac3Param", mac3ParamValue, STRING_LEN, "text", "12:34:56:78:9A:BC", "");

/**
 * This class IS A FRICKIN MESS.
 */
class SN_IotWebConf {
    public:
        SN_IotWebConf();
        SN_IotWebConf(SN_LoopControl::Mode *mode, DateTime *cntUpStart, DateTime *cntDownEnd);
		void setup();
        void setTimeParamsUpdated(boolean isUpdated);
		void doLoop();
        char* getDateTimeParam();
        char* getTZIDParam();
        boolean getIsTimeParamsUpdated();
        boolean getIsAutoTime();
        /*char *getMac1Param();
        char *getMac2Param();
        char *getMac3Param();*/

    private:
        static SN_LoopControl::Mode *currentMode;
        static DateTime *countUpStart;
        static DateTime *countDownEnd;
        static boolean isTimeParamsUpdated;
        static boolean isAutoTime;
        static boolean formValidator();
        static void onConfigSaved();
        static void onConnect();
        static void handleRoot();   // methods provided to server.on must be static (or binded, but you dont want that)
        static void onClockState();
        static void onCountUpState();
        static void onCountDownState();
        static void onSensorState();
        static void onOffState();
        static RTC_DS3231 rtc;

};

#endif
