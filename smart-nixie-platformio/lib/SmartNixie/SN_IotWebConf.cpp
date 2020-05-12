#include "SN_IotWebConf.h"

SN_IotWebConf::SN_IotWebConf() {
	//NOP
}

void SN_IotWebConf::setup() {
	Serial.println("Starting up...");

	iotWebConf.setStatusPin(STATUS_PIN);
	iotWebConf.setConfigPin(CONFIG_PIN);
	iotWebConf.addParameter(&timeSeparator);
	iotWebConf.addParameter(&dateTimeParam);
	iotWebConf.addParameter(&tzidParam);
	iotWebConf.addParameter(&turnoffSeparator);
	iotWebConf.addParameter(&mac1Param);
	iotWebConf.addParameter(&mac2Param);
	iotWebConf.addParameter(&mac3Param);
	//iotWebConf.addParameter(&stringParam);
	//iotWebConf.addParameter(&separator1);
	//iotWebConf.addParameter(&intParam);
	//iotWebConf.addParameter(&separator2);
	//iotWebConf.addParameter(&floatParam);
	iotWebConf.setConfigSavedCallback(&configSaved);
	iotWebConf.setFormValidator(&formValidator);

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
	s += "<title>SmartNixie setup page</title></head><body>Hello world!";
	s += "<ul>";
	s += "<li>Time param value: ";
	s += dateTimeParamValue;
	s += "<li>TZID param value: ";
	s += tzidParamValue;
	s += "<li>MAC1 param value: ";
	s += mac1ParamValue;
	s += "<li>MAC2 param value: ";
	s += mac2ParamValue;
	s += "<li>MAC3 param value: ";
	s += mac3ParamValue;
	//s += "<li>Int param value: ";
	//s += atoi(intParamValue);
	//s += "<li>Float param value: ";
	//s += atof(floatParamValue);
	s += "</ul>";
	s += "Go to <a href='config'>configure page</a> to change values.";
	s += "</body></html>\n";

	server.send(200, "text/html", s);
}

void SN_IotWebConf::configSaved() {
	Serial.println("Configuration was updated.");
}

boolean SN_IotWebConf::formValidator() {
	Serial.println("Validating form.");
	boolean valid = true;

	int l = server.arg(tzidParam.getId()).length();
	if (l < 3) {
		tzidParam.errorMessage = "Please provide at least 3 characters for this test!";
		valid = false;
	}

	return valid;
}
