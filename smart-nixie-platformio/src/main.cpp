#include <Arduino.h>
#include "Adafruit_MCP23017.h"
#include "Display.h"

// 1100 value turns off the tube!

Adafruit_MCP23017 mcp;
Display disp(mcp);
int value;

void setup() {
  Serial.begin(9600);
}

void loop() {

  value = map(analogRead(A0), 0, 1023, 0, 99);
  disp.show(value);
  delay(150);
  
}
