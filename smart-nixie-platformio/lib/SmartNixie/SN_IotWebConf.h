#ifndef SN_IOTWEBCONF_H
#define SN_IOTWEBCONF_H

#include <Arduino.h>
#include <IotWebConf.h>

const char thingName[] = "smart-nixie";
const char wifiInitialApPassword[] = "123456";
static DNSServer dnsServer;
static WebServer server(80);

static IotWebConf iotWebConf(thingName, &dnsServer, &server, wifiInitialApPassword);

class SN_IotWebConf {
    public:
        SN_IotWebConf();
		void setup();
		void doLoop();

    private:
        static void handleRoot();   // methods provided to server.on must be static (or binded, but you dont want that)

};

#endif
