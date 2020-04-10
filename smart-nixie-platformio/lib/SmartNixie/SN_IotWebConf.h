#ifndef SN_IOTWEBCONF_H
#define SN_IOTWEBCONF_H

#include <Arduino.h>
#include <IotWebConf.h>

#define STRING_LEN 128
#define NUMBER_LEN 32
#define CONFIG_VERSION "dem2"
#define CONFIG_PIN D4
#define STATUS_PIN LED_BUILTIN

class SN_IotWebConf {
    public:
        SN_IotWebConf();
    private:
		const char thingName[];
		const char wifiInitialApPassword[];
		void configSaved();
		boolean formValidator();
		DNSServer dnsServer;
};

#endif
