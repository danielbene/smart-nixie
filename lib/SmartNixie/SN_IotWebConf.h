#ifndef SN_IOTWEBCONF_H
#define SN_IOTWEBCONF_H

#include <Arduino.h>
#include <ESP8266mDNS.h>
#include <ESP8266WiFiMulti.h>
#include <IotWebConf.h>
#include <RTClib.h>

#include "SN_LoopControl.h"
#include "Util.h"

#define CONFIG_VERSION "nixie.1"
#define CONFIG_PIN D5
#define STATUS_PIN LED_BUILTIN
#define IP_ADDRESS_LENGTH 15

const char thingName[] = "nixie";
const char wifiInitialApPassword[] = "12345678";
static DNSServer dnsServer;
static ESP8266WebServer server(80);

static IotWebConf iotWebConf(thingName, &dnsServer, &server, wifiInitialApPassword);

static char dateTimeParamValue[20];
static char tzOffsetHours[3];
static char slotmachineTimeParamValue[6];
static char blankingLeftZerosParamValue[2];

static char staticIpParamValue[IP_ADDRESS_LENGTH];
static char gatewayIpParamValue[IP_ADDRESS_LENGTH];
static char subnetMaskParamValue[IP_ADDRESS_LENGTH];
static char dnsServerParamValue[IP_ADDRESS_LENGTH];

static IotWebConfSeparator timeSeparator = IotWebConfSeparator("Manual/Auto time settings");
static IotWebConfParameter dateTimeParam = IotWebConfParameter("Current time for manual setup", "dateTimeParam", dateTimeParamValue, 20, "text", "2020.01.01 11:00:00", "");
//TODO: add offset field validation
static IotWebConfParameter tzOffsetParam = IotWebConfParameter("Timezone offset from UTC in hours", "tzOffset", tzOffsetHours, 3, "text", "-1", "");
static IotWebConfSeparator otherSeparator = IotWebConfSeparator("Other settings");
static IotWebConfParameter slotmachineTimeParam = IotWebConfParameter("Slotmachine time (cathode poisoning prevention)", "slotmachineTimeParam", slotmachineTimeParamValue, 6, "text", "21:00", "21:00");
//using text based true/false temporarly - iotwebconf do not handle checkbox well yet
static IotWebConfParameter blankingLeftZerosParam = IotWebConfParameter("Blanking left side zero tubes", "blankingLeftZero", blankingLeftZerosParamValue, 2, "text", "Y or N", "N");

static IotWebConfSeparator staticIpSeparator = IotWebConfSeparator("Static IP settings (optional)");
static IotWebConfParameter staticIpParam = IotWebConfParameter("Static IP address for the nixie clock", "staticIp", staticIpParamValue, IP_ADDRESS_LENGTH, "text", "192.168.1.2", "");
static IotWebConfParameter gatewayIpParam = IotWebConfParameter("IP address of the network gateway (usually the router)", "gatewayIp", gatewayIpParamValue, IP_ADDRESS_LENGTH, "text", "192.168.1.1", "");
static IotWebConfParameter subnetMaskParam = IotWebConfParameter("Subnet mask of the network", "subnetMask", subnetMaskParamValue, IP_ADDRESS_LENGTH, "text", "255.255.255.0", "");
static IotWebConfParameter dnsServerParam = IotWebConfParameter("IP address of the choosen DNS server", "dnsServer", dnsServerParamValue, IP_ADDRESS_LENGTH, "text", "1.1.1.1", "");


class SN_IotWebConf {
    public:
        SN_IotWebConf();
        SN_IotWebConf(SN_LoopControl::Mode *mode, DateTime *cntUpStart, DateTime *cntDownEnd);
        static boolean isConnected;
		void setup();
		void doLoop();
        char *getBlankingLeftZerosParam();
        char *getDateTimeParam();
        char *getTZOffsetParam();
        char *getSlotmachineTimeParam();

    private:
        static SN_LoopControl::Mode *currentMode;
        static DateTime *countUpStart;
        static DateTime *countDownEnd;
        static boolean formValidator();
        static void staticIpUpdater();
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
