#ifndef SN_IOTWEBCONF_H
#define SN_IOTWEBCONF_H

#include <Arduino.h>
#include <IotWebConf.h>

#define CONFIG_VERSION "asd0"
#define CONFIG_PIN D5
#define STATUS_PIN LED_BUILTIN

#define STRING_LEN 128
#define NUMBER_LEN 32

const char thingName[] = "smart-nixie";
const char wifiInitialApPassword[] = "123456";
static DNSServer dnsServer;
static WebServer server(80);

static IotWebConf iotWebConf(thingName, &dnsServer, &server, wifiInitialApPassword);

static char dateTimeParamValue[STRING_LEN];
static char tzidParamValue[STRING_LEN];
static char mac1ParamValue[STRING_LEN];
static char mac2ParamValue[STRING_LEN];
static char mac3ParamValue[STRING_LEN];
//static char stringParamValue[STRING_LEN];
//static char intParamValue[NUMBER_LEN];
//static char floatParamValue[NUMBER_LEN];
static IotWebConfSeparator timeSeparator = IotWebConfSeparator("Manual/Auto time settings");
static IotWebConfParameter dateTimeParam = IotWebConfParameter("Current time for manual setup", "dateTimeParam", dateTimeParamValue, STRING_LEN, "text", "2020.12.25 13:30:25", NULL);
static IotWebConfParameter tzidParam = IotWebConfParameter("Timezone for automatic setup", "tzidParam", tzidParamValue, STRING_LEN, "text", "Europe/Budapest", NULL);
static IotWebConfSeparator turnoffSeparator = IotWebConfSeparator("Auto turnoff settings");
static IotWebConfParameter mac1Param = IotWebConfParameter("Device 1 MAC address", "mac1Param", mac1ParamValue, STRING_LEN, "text", "12:34:56:78:9A:BC", NULL);
static IotWebConfParameter mac2Param = IotWebConfParameter("Device 2 MAC address", "mac2Param", mac2ParamValue, STRING_LEN, "text", "12:34:56:78:9A:BC", NULL);
static IotWebConfParameter mac3Param = IotWebConfParameter("Device 3 MAC address", "mac3Param", mac3ParamValue, STRING_LEN, "text", "12:34:56:78:9A:BC", NULL);
//static IotWebConfSeparator separator1 = IotWebConfSeparator();
//static IotWebConfParameter intParam = IotWebConfParameter("Int param", "intParam", intParamValue, NUMBER_LEN, "number", "1..100", NULL, "min='1' max='100' step='1'");
//static IotWebConfSeparator separator2 = IotWebConfSeparator("Calibration factor");
//static IotWebConfParameter floatParam = IotWebConfParameter("Float param", "floatParam", floatParamValue, NUMBER_LEN, "number", "e.g. 23.4", NULL, "step='0.1'");

class SN_IotWebConf {
    public:
        SN_IotWebConf();
		void setup();
		void doLoop();

    private:
        static void configSaved();
        static boolean formValidator();
        static void handleRoot();   // methods provided to server.on must be static (or binded, but you dont want that)

};

#endif
