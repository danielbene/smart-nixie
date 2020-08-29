#include "SN_IotWebConf.h"

SN_LoopControl::Mode *SN_IotWebConf::currentMode = NULL;
DateTime *SN_IotWebConf::countUpStart = NULL;
DateTime *SN_IotWebConf::countDownEnd = NULL;
boolean SN_IotWebConf::isConnected = false;

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

	iotWebConf.setStatusPin(STATUS_PIN);
	iotWebConf.setConfigPin(CONFIG_PIN);
	iotWebConf.addParameter(&timeSeparator);
	iotWebConf.addParameter(&dateTimeParam);
	iotWebConf.addParameter(&tzOffsetParam);
	iotWebConf.addParameter(&otherSeparator);
	iotWebConf.addParameter(&slotmachineTimeParam);
	iotWebConf.addParameter(&staticIpSeparator);
	iotWebConf.addParameter(&staticIpParam);
	iotWebConf.addParameter(&gatewayIpParam);
	iotWebConf.addParameter(&subnetMaskParam);
	iotWebConf.addParameter(&dnsServerParam);
	iotWebConf.setConfigSavedCallback(&onConfigSaved);
	iotWebConf.setWifiConnectionCallback(&onConnect);
	iotWebConf.setFormValidator(&formValidator);

	iotWebConf.init();

	if ((staticIpParam.valueBuffer != NULL) && (staticIpParam.valueBuffer[0] != '\0')) {
		IPAddress staticIp, gateway, subnet, dns;
		staticIp.fromString(staticIpParamValue);
		gateway.fromString(gatewayIpParamValue);
		subnet.fromString(subnetMaskParamValue);
		dns.fromString(dnsServerParamValue);

		WiFi.config(staticIp, gateway, subnet, dns);
		Util::printDebugLine("SET UP STATIC IP BASED ON STORED PARAMETERS", true);
	}

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

char *SN_IotWebConf::getTZOffsetParam() {
	return &tzOffsetHours[0];
}

char *SN_IotWebConf::getSlotmachineTimeParam() {
	return &slotmachineTimeParamValue[0];
}

void SN_IotWebConf::onConfigSaved() {
	staticIpUpdater();
	Util::printDebugLine("Configuration was updated.", true);
}

void SN_IotWebConf::onConnect() {
	MDNS.close();
	delay(100);

	MDNS.begin(SN_MDNS_NAME); // will be reachable on SN_MDNS_NAME.local URL (Android do not support mDNS URLs)

	isConnected = true;
}

boolean SN_IotWebConf::formValidator() {
	Util::printDebugLine("Validating form.", true);
	boolean valid = true;

	if (valid && !Util::isValidDateTime(server.arg(dateTimeParam.getId()).c_str()) && !server.arg(dateTimeParam.getId()).equals("")) {
		dateTimeParam.errorMessage = "Invalid date! Please use the example format.";
		valid = false;
	}

	if (valid && !Util::isValidTime(server.arg(slotmachineTimeParam.getId()).c_str()) && !server.arg(slotmachineTimeParam.getId()).equals("")) {
		slotmachineTimeParam.errorMessage = "Invalid slotmachine time! Please use the example format.";
		valid = false;
	}

	//valid if all params empty, or all params filled
	if (valid && !((server.arg(staticIpParam.getId()).equals("") && server.arg(gatewayIpParam.getId()).equals("")
	&& server.arg(subnetMaskParam.getId()).equals("") && server.arg(dnsServerParam.getId()).equals(""))
	|| (!server.arg(staticIpParam.getId()).equals("") && !server.arg(gatewayIpParam.getId()).equals("")
	&& !server.arg(subnetMaskParam.getId()).equals("") && !server.arg(dnsServerParam.getId()).equals("")))) {
		staticIpParam.errorMessage = "All parameters required for proper static IP setup!";
		gatewayIpParam.errorMessage = "All parameters required for proper static IP setup!";
		subnetMaskParam.errorMessage = "All parameters required for proper static IP setup!";
		dnsServerParam.errorMessage = "All parameters required for proper static IP setup!";
		valid = false;
	}

	if (valid && (!server.arg(staticIpParam.getId()).equals("") && !server.arg(gatewayIpParam.getId()).equals("")
	&& !server.arg(subnetMaskParam.getId()).equals("") && !server.arg(dnsServerParam.getId()).equals(""))) {
		//if all IP params filled then validate them separately
		if (valid && !Util::isValidIpAddress(server.arg(staticIpParam.getId()))) {
			staticIpParam.errorMessage = "Invalid IP address.";
			valid = false;
		}

		if (valid && !Util::isValidIpAddress(server.arg(gatewayIpParam.getId()))) {
			gatewayIpParam.errorMessage = "Invalid IP address.";
			valid = false;
		}

		if (valid && !Util::isValidIpAddress(server.arg(subnetMaskParam.getId()))) {
			subnetMaskParam.errorMessage = "Invalid IP address.";
			valid = false;
		}

		if (valid && !Util::isValidIpAddress(server.arg(dnsServerParam.getId()))) {
			dnsServerParam.errorMessage = "Invalid IP address.";
			valid = false;
		}
	}

	return valid;
}

void SN_IotWebConf::staticIpUpdater() {
	if (!server.arg(staticIpParam.getId()).equals("")) {
		//set static IP
		IPAddress staticIp, gateway, subnet, dns;
		staticIp.fromString(staticIpParamValue);
		gateway.fromString(gatewayIpParamValue);
		subnet.fromString(subnetMaskParamValue);
		dns.fromString(dnsServerParamValue);

		WiFi.disconnect();
		WiFi.config(staticIp, gateway, subnet, dns);
		delay(100);

		WiFi.begin(iotWebConf.getWifiSsidParameter()->valueBuffer, iotWebConf.getWifiPasswordParameter()->valueBuffer);

		Util::printDebugLine("WIFI STATIC IP CONFIGURATION UPDATED", true);
	} else {
		//back to DHCP
		WiFi.disconnect();
		delay(100);

		WiFi.begin(iotWebConf.getWifiSsidParameter()->valueBuffer, iotWebConf.getWifiPasswordParameter()->valueBuffer);
		WiFi.config(0U, 0U, 0U, 0U);

		Util::printDebugLine("WIFI DYNAMIC IP (DHCP) CONFIGURATION UPDATED", true);
	}
}

void SN_IotWebConf::handleRoot() {
	if (iotWebConf.handleCaptivePortal()) return;

	// TODO: static page handling with spiffs?
	String s = "<!DOCTYPE html><html lang=\"en\"><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\"/><title>SmartNixie</title><style>.button {border: none; color: white; padding: 15px 32px; text-align: center; text-decoration: none; display: inline-block; font-size: 16px; margin: 4px 2px; cursor: pointer;} .button1 {background-color: #4CAF50;} /* Green */ .button1:active {background-color: grey;} .button2 {background-color: #008CBA;} /* Blue */ .button2:active {background-color: grey;} </style></head><body><h1>SmartNixie control page!</h1><form action=\"/clock\" method=\"POST\"><button class=\"button button1\" type=\"submit\">CLOCK</button></br></form><form action=\"/countup\" method=\"POST\"><button class=\"button button2\" type=\"submit\">COUNTUP</button></br></form><form action=\"/countdown\" method=\"POST\"><button class=\"button button1\" type=\"submit\">COUNTDOWN</button><input type=\"text\" name=\"minutes\" value=\"0\"></br></form><form action=\"/sensor\" method=\"POST\"><button class=\"button button2\" type=\"submit\">SENSOR</button></br></form><form action=\"/off\" method=\"POST\"><button class=\"button button1\" type=\"submit\">OFF</button></br></form><p>Go to <a href='config'>configure page</a> to change values.</p></body></html>";

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
	int minutes = server.arg("minutes").toInt(); // web page text input field
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
