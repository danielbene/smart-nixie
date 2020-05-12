#include <Arduino.h>
#include <IotWebConf.h>
#include "SN_LoopControl.h"

//#define DELAY 250
#define DELAY 1500
#define THING_NAME "smart-nixie"
#define AP_INIT_PASSWD "123456"

SN_LoopControl snLoopControl = SN_LoopControl();
SN_LoopControl::Mode mode;

DNSServer dnsServer;
WebServer server(80);
IotWebConf iotWebConf(THING_NAME, &dnsServer, &server, AP_INIT_PASSWD);

unsigned long loopTs = millis() + DELAY;
boolean test = false;

void handleRoot();

void setup() {
    Serial.begin(115200);

    iotWebConf.init();
    server.on("/", handleRoot);
    server.on("/config", []{ iotWebConf.handleConfig(); });
    server.onNotFound([](){ iotWebConf.handleNotFound(); });
}

void loop() {
    iotWebConf.doLoop();

    // non-blocking delay
    if (millis() >= loopTs) {
        if (test) {
            mode = SN_LoopControl::Mode::CLOCK;
        } else {
            mode = SN_LoopControl::Mode::SENSOR;
        }

        test = !test;

        snLoopControl.doLoop(mode);
        loopTs = millis() + DELAY;
    }
}

void handleRoot() {
    if (iotWebConf.handleCaptivePortal()) {
        return;
    }

    String s = "<!DOCTYPE html><html lang=\"en\"><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\"/>";
    s += "<title>IotWebConf 01 Minimal</title></head><body>Hello world!";
    s += "Go to <a href='config'>configure page</a> to change settings.";
    s += "</body></html>\n";

    server.send(200, "text/html", s);
}
