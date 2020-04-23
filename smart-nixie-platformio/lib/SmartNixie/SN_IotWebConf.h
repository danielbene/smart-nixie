#ifndef SN_IOTWEBCONF_H
#define SN_IOTWEBCONF_H

#include <Arduino.h>
#include <IotWebConf.h>

const char thingName[] = "smart-nixie";
const char wifiInitialApPassword[] = "123456";
DNSServer dnsServer;
WebServer server(80);

IotWebConf iotWebConf(thingName, &dnsServer, &server, wifiInitialApPassword);

class SN_IotWebConf {
    public:
        SN_IotWebConf();
		void setup();
		void doLoop();
    private:
};

#endif
