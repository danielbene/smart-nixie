#include <Arduino.h>
#include "SN_Clock.h"

SN_Clock snClock;

void setup() {
  Serial.begin(9600);

  snClock.setTime(DateTime(2020, 4, 5, 12, 30, 0));
}

void loop() {

  snClock.displayCurrentTime();

  delay(250);

}
