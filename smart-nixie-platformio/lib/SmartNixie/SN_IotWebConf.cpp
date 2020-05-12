#include "SN_IotWebConf.h"

SN_IotWebConf::SN_IotWebConf() {
	//NOP
}

void SN_IotWebConf::setup() {
	Serial.println("Starting up...");

	iotWebConf.init();

	server.on("/", handleRoot);
	server.on("/config", []{ iotWebConf.handleConfig(); });
	server.onNotFound([](){ iotWebConf.handleNotFound(); });

	Serial.println("Ready.");
}

void SN_IotWebConf::doLoop() {
	iotWebConf.doLoop();
}

void SN_IotWebConf::handleRoot() {
	if (iotWebConf.handleCaptivePortal()) {
		return;
	}

	String s = "<!DOCTYPE html><html lang=\"en\"><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\"/>";
	s += "<title>IotWebConf 01 Minimal</title></head><body>Hello world!";
	s += "Go to <a href='config'>configure page</a> to change settings.";
	s += "</body></html>\n";

	server.send(200, "text/html", s);
}
