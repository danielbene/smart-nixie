#include "SN_IotWebConf.h"

SN_LoopControl::Mode *SN_IotWebConf::currentMode = NULL;
DateTime *SN_IotWebConf::countUpStart = NULL;
DateTime *SN_IotWebConf::countDownEnd = NULL;
boolean SN_IotWebConf::isTimeParamsUpdated = false;
boolean SN_IotWebConf::isAutoTime = false;

SN_IotWebConf::SN_IotWebConf() {
	//NOP
}

SN_IotWebConf::SN_IotWebConf(SN_LoopControl::Mode *mode, DateTime *cntUpStart, DateTime *cntDownEnd) {
	currentMode = mode;
	countUpStart = cntUpStart;
	countDownEnd = cntDownEnd;
}

void SN_IotWebConf::setup() {
	Util::printDebugLine("Starting up...", true);

	/*IPAddress staticIp(192, 168, 100, 21);
	IPAddress gateway(192, 168, 100, 1);
	IPAddress subnet(255, 255, 255, 0);
	IPAddress dns(1, 1, 1, 1);
	WiFi.config(staticIp, gateway, subnet, dns);*/

	iotWebConf.setStatusPin(STATUS_PIN);
	iotWebConf.setConfigPin(CONFIG_PIN);
	iotWebConf.addParameter(&timeSeparator);
	iotWebConf.addParameter(&dateTimeParam);
	iotWebConf.addParameter(&tzidParam);
	/*iotWebConf.addParameter(&turnoffSeparator);
	iotWebConf.addParameter(&mac1Param);
	iotWebConf.addParameter(&mac2Param);
	iotWebConf.addParameter(&mac3Param);*/
	iotWebConf.setConfigSavedCallback(&onConfigSaved);
	iotWebConf.setWifiConnectionCallback(&onConnect);
	iotWebConf.setFormValidator(&formValidator);

	iotWebConf.init();

	server.on("/", handleRoot);
	server.on("/config", []{ iotWebConf.handleConfig(); });
	server.on("/clock", onClockState);
	server.on("/countup", onCountUpState);
	server.on("/countdown", onCountDownState);
	server.on("/sensor", onSensorState);
	server.on("/off", onOffState);
	server.onNotFound([](){ iotWebConf.handleNotFound(); });

	Util::printDebugLine("Ready.", true);
}

void SN_IotWebConf::doLoop() {
	MDNS.update();
	iotWebConf.doLoop();
}

char *SN_IotWebConf::getDateTimeParam() {
	return &dateTimeParamValue[0];
}

char *SN_IotWebConf::getTZIDParam() {
	return tzidParamValue;
}

/*char *SN_IotWebConf::getMac1Param() {
	return mac1ParamValue;
}

char *SN_IotWebConf::getMac2Param() {
	return mac2ParamValue;
}

char *SN_IotWebConf::getMac3Param() {
	return mac3ParamValue;
}*/

void SN_IotWebConf::onConfigSaved() {
	Util::printDebugLine("Configuration was updated.", true);

	if (dateTimeParamValue != "" || tzidParamValue != "") {
		isTimeParamsUpdated = true;
		if (dateTimeParamValue != "") {
			isAutoTime = false;
		} else {
			isAutoTime = true;
		}
	}
}

void SN_IotWebConf::onConnect() {
	MDNS.close();
	delay(100);

	// after reinit (takes some time) it is reachable on nixie.local dns (on the local network)
	// android do not support mdns
	MDNS.begin("nixie");
}

boolean SN_IotWebConf::formValidator() {
	Util::printDebugLine("Validating form.", true);
	boolean valid = true;

	if (valid && !Util::isValidDate(server.arg(dateTimeParam.getId()).c_str()) && !server.arg(dateTimeParam.getId()).equals("")) {
		dateTimeParam.errorMessage = "Invalid date! Please use the example format.";
		valid = false;
	}

	/*if (valid && !Util::isValidMacAddress(server.arg(mac1Param.getId()).c_str()) && !server.arg(mac1Param.getId()).equals("")) {
		mac1Param.errorMessage = "Not a valid MAC address!";
		valid = false;
	}

	if (valid && !Util::isValidMacAddress(server.arg(mac2Param.getId()).c_str()) && !server.arg(mac2Param.getId()).equals("")) {
		mac2Param.errorMessage = "Not a valid MAC address!";
		valid = false;
	}

	if (valid && !Util::isValidMacAddress(server.arg(mac3Param.getId()).c_str()) && !server.arg(mac3Param.getId()).equals("")) {
		mac3Param.errorMessage = "Not a valid MAC address!";
		valid = false;
	}*/

	return valid;
}

void SN_IotWebConf::handleRoot() {
	if (iotWebConf.handleCaptivePortal()) return;

	// TODO: static page handling with spiffs?
	String s = "<!DOCTYPE html><html lang=\"en\"><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\"/><title>SmartNixie</title><style>.button {border: none; color: white; padding: 15px 32px; text-align: center; text-decoration: none; display: inline-block; font-size: 16px; margin: 4px 2px; cursor: pointer;} .button1 {background-color: #4CAF50;} /* Green */ .button1:active {background-color: grey;} .button2 {background-color: #008CBA;} /* Blue */ .button2:active {background-color: grey;} </style></head><body><h1>SmartNixie control page!</h1><form action=\"/clock\" method=\"POST\"><button class=\"button button1\" type=\"submit\">CLOCK</button></br></form><form action=\"/countup\" method=\"POST\"><button class=\"button button2\" type=\"submit\">COUNTUP</button></br></form><form action=\"/countdown\" method=\"POST\"><button class=\"button button1\" type=\"submit\">COUNTDOWN</button><input type=\"text\" name=\"minutes\" value=\"0\"></br></form><form action=\"/sensor\" method=\"POST\"><button class=\"button button2\" type=\"submit\">SENSOR</button></br></form><form action=\"/off\" method=\"POST\"><button class=\"button button1\" type=\"submit\">OFF</button></br></form><p>Go to <a href='config'>configure page</a> to change values.</p></body></html>";

	/*String s = "<!DOCTYPE html><html lang=\"en\"><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\"/>";
	s += "<title>SmartNixie setup page</title></head><body>Hello world!";
	s += "<ul>";
	s += "<li>Time param value: ";
	s += dateTimeParamValue;
	s += "<li>TZID param value: ";
	s += tzidParamValue;*/
	/*s += "<li>MAC1 param value: ";
	s += mac1ParamValue;
	s += "<li>MAC2 param value: ";
	s += mac2ParamValue;
	s += "<li>MAC3 param value: ";
	s += mac3ParamValue;*/
	/*s += "</ul>";
	s += "Go to <a href='config'>configure page</a> to change values.";
	s += "</body></html>\n";*/

	server.send(200, "text/html", s);
}

// method address passing (in the server.on) requires these to be in separate functions
void SN_IotWebConf::onClockState() {
	*currentMode = SN_LoopControl::Mode::CLOCK;
	Util::printDebugLine("CLOCK MODE SET", true);
	handleRoot();
}

void SN_IotWebConf::onCountUpState() {
	*currentMode = SN_LoopControl::Mode::COUNTUP;
	*countUpStart = rtc.now();
	Util::printDebugLine("COUNTUP MODE SET", true);
	handleRoot();
}

void SN_IotWebConf::onCountDownState() {
	int minutes = server.arg("minutes").toInt();	// web page text input field
	*currentMode = SN_LoopControl::Mode::COUNTDOWN;
	*countDownEnd = Util::calculateFutureTime(minutes);

	String msg[] = {"COUNTDOWN MODE SET", ", minutes = ", String(minutes)};
	Util::printDebugLine(msg, 3, true);

	handleRoot();
}

void SN_IotWebConf::onSensorState() {
	*currentMode = SN_LoopControl::Mode::SENSOR;
	Util::printDebugLine("SENSOR MODE SET", true);
	handleRoot();
}

void SN_IotWebConf::onOffState() {
	*currentMode = SN_LoopControl::Mode::OFF;
	Util::printDebugLine("OFF MODE SET", true);
	handleRoot();
}
