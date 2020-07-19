#include "Util.h"

boolean Util::isValidDate(const char *dateTime) {
	//TODO: proper datetime validation for format - yyyy.mm.dd HH24:mm:ss
    printDebugLine("UNIMPLEMENTED METHOD USED! - Util::isValidDate", true);
	return true;
}

boolean Util::isValidMacAddress(const char *mac) {
	int i = 0;
	int s = 0;

	while (*mac) {
		if (isxdigit(*mac)) {
			i++;
		} else if (*mac == ':') {
			if (i == 0 || i / 2 - 1 != s) break;
			++s;
		} else {
			s = -1;
		}

		++mac;
	}

	return (i == 12 && s == 5);
}

DateTime Util::calculateFutureTime(int32_t minutes) {
	int days = minutes / 60 / 24;
    int hours = minutes / 60 % 24;
    minutes = minutes % 60;

    return rtc.now() + TimeSpan(days, hours, minutes, 0);
}

/**
 * Convert char pointer (c str) to DateTime object.
 * Needed pattern: yyyy.mm.dd hh:mm:ss
**/
DateTime Util::charToDateTime(char *dateStr) {
	tm tm1;
	sscanf(dateStr,"%4d.%2d.%2d %2d:%2d:%2d",&tm1.tm_year, &tm1.tm_mon,
            &tm1.tm_mday, &tm1.tm_hour, &tm1.tm_min, &tm1.tm_sec);

    return DateTime(tm1.tm_year, tm1.tm_mon, tm1.tm_mday, tm1.tm_hour, tm1.tm_min, tm1.tm_sec);
}

void Util::printDebugLine(String param, boolean addNewLine) {
	if (SN_DEBUG) {
		Serial.print(param);
		if (addNewLine) Serial.println();
	}
}

void Util::printDebugLine(String params[], int paramSize, boolean addNewLine) {
	if (SN_DEBUG) {
		for (int i = 0; i < paramSize; i++) {
			Serial.print(params[i]);
		}

		if (addNewLine) Serial.println();
	}
}
