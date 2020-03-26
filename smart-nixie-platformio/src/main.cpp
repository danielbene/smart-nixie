#include <Arduino.h>
#include "Adafruit_MCP23017.h"
#include "Tube.h"

Adafruit_MCP23017 mcpObj;
int pins[] = {11, 10, 9, 8};
int value = 0;

// 1100 value turns off the tube!

void setup() {
  Serial.begin(9600);

  // these go in the clock class later
  mcpObj.begin(); // pinmode setup in Tube obj constructor, so begin needs before that
  Tube firstTube(pins, mcpObj);

  firstTube.writeNum(3);
  delay(1000);
  firstTube.writeNum(0);
  delay(1000);
  firstTube.writeNum(9);
  delay(1000);
  firstTube.writeNum(5);
  delay(1000);
}

void loop() {
}
