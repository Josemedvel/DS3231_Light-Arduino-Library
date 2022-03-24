#include <Wire.h>
#include "DS3231_Light.h"



void setup() {
 Serial.begin(9600);
}

void loop() {
  readRTC();
  Serial.print(extractHour());
  Serial.print(":");
  Serial.print(extractMinutes());
  Serial.print(":");
  Serial.println(extractSeconds());
  delay(SECOND);

}
