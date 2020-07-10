#include "Util.h"

boolean Util::isValidDate(const char* dateTime) {
	//TODO: proper datetime validation for format - yyyy.mm.dd HH24:mm:ss
    Serial.println("UNIMPLEMENTED METHOD USED! - Util::isValidDate");
	return true;
}

boolean Util::isValidMacAddress(const char* mac) {
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
