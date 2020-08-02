#include "Util.h"

boolean Util::isValidDateTime(const char *dateTime) {
	boolean isValid = true;
	std::string dt = dateTime;

	if (dt.length() != 19) {
		isValid = false;
	} else if (dt.at(4) != '.' || dt.at(7) != '.' || dt.at(10) != ' ' || dt.at(13) != ':' ||  dt.at(16) != ':') {
		isValid = false;
	} else {
		//parse after basic format tests to avoid some malformed input errors
		int month = atoi(dt.substr(5, 2).c_str());
		int day = atoi(dt.substr(8, 2).c_str());
		int hour = atoi(dt.substr(11, 2).c_str());
		int minute = atoi(dt.substr(14, 2).c_str());
		int second = atoi(dt.substr(17, 2).c_str());

		isValid = (month >= 0 && month <= 12)
			&& (day >= 0 && day <= 31)
			&& (hour >= 0 && hour <= 24)
			&& (minute >= 0 && minute <= 60)
			&& (second >= 0 && second <= 60);
	}

	return isValid;
}

boolean Util::isValidTime(const char *time) {
	int hour, minute;

	std::string s = time;
	hour = atoi(s.substr(0, s.find(":")).c_str());
	minute = atoi(s.substr(s.find(":") + 1, s.length()).c_str());

	return (hour >= 0 && hour <= 24) && (minute >= 0 && minute <= 60);
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
	sscanf(dateStr, "%4d.%2d.%2d %2d:%2d:%2d", &tm1.tm_year, &tm1.tm_mon,
            &tm1.tm_mday, &tm1.tm_hour, &tm1.tm_min, &tm1.tm_sec);

    return DateTime(tm1.tm_year, tm1.tm_mon, tm1.tm_mday, tm1.tm_hour, tm1.tm_min, tm1.tm_sec);
}

DateTime Util::charToTime(char *timeStr) {
	tm tm1;
	sscanf(timeStr, "%2d:%2d", &tm1.tm_hour, &tm1.tm_min);

    return DateTime(1970, 1, 1, tm1.tm_hour, tm1.tm_min, 1);
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
