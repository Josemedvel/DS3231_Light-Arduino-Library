#include <Wire.h>
#include "DS3231_Light.h"



void setup() {
  Serial.begin(9600);
  //setHour(12);
  //setMinutes(39);
  //setMonth(3);
  //setYear(2022);
  //setMonthDay(25);
  //setFullDate(30,3,2020);
}

void loop() {
  readRTC();
  Serial.println(getDS3231Time());
  //Serial.println(getWeekDay());
  Serial.println(getWeekDayName());
  Serial.println(getDS3231Date());
  //Serial.println(getDoW(getMonthDay(),getMonth(),getYear()));
  delay(SECOND);

}
