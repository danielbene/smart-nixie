#include <Arduino.h>
#include "SN_Clock.h"

SN_Clock snClock;

void setup() {
  Serial.begin(9600);
}

void loop() {

  snClock.serialClock();
 
  delay(2000);
  
}
