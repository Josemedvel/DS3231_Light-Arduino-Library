#include "DS3231_Light.h"
#include <Wire.h>

DS3231_Light RTC;
//No century or alarm support in this library!

//number control
int BCDToBinary(uint8_t number) {
  uint8_t firstH = ((number & 0b11110000) >> 4) * 10;
  uint8_t lastH = (number & 0b00001111);
  return firstH + lastH;
}


uint8_t binaryToBCD(uint8_t number) {
  uint8_t result = 0b0;
  result |= number / 10;
  result = result << 4;
  result |= number % 10;
  return result;
}

//read registers
int readRTC() {
  Wire.begin();
  Wire.beginTransmission(ADDRESS);
  Wire.write(0x00);//first register
  Wire.requestFrom(ADDRESS, 7);
  RTC.seconds = Wire.read();
  RTC.minutes = Wire.read();
  RTC.hours = Wire.read();
  RTC.weekDay = Wire.read();
  RTC.dateDay = Wire.read();
  RTC.months = Wire.read();
  RTC.years = Wire.read();
  
  if (Wire.endTransmission() != 0) {
    return -1;//Reading error
  }
  return 0;
}


//getter functions
int getHour() {
  if ((RTC.hours & 0b0100000) == 0) { //check 12 hours mode
    return BCDToBinary(RTC.hours & 0b00011111);
  }
  // We are in 24 hours mode
  return BCDToBinary(RTC.hours & 0b00111111);
}


int getMinutes() {
  return BCDToBinary(RTC.minutes);
}


int getSeconds() {
  return BCDToBinary(RTC.seconds);
}


int getWeekDay() {
  return BCDToBinary(RTC.weekDay);
}


String getWeekDayName() {
  return weekDayNames[RTC.weekDay - 1];
}


int getMonthDay() {
  return BCDToBinary(RTC.dateDay);
}


int getMonth() {
  return BCDToBinary(RTC.months & 0b01111111);
}


int getYear() {
  return getCentury() + BCDToBinary(RTC.years);
}


int getCentury() {
  if ((RTC.months & 0b10000000) != 0b10000000) { //21st century
    return 2000;
  }
  //20th century
  return 1900;
}


String getDS3231Time() {
  
  String finalTime = "";
  int hours = getHour();
  int minutes = getMinutes();
  int seconds = getSeconds();
  
  if (hours < 10) {
    finalTime += "0";
    finalTime += hours;
  }
  else {
    finalTime += hours;
  }
  
  finalTime += ":";
  
  if (minutes < 10) {
    finalTime += "0";
    finalTime += minutes;
  }
  else {
    finalTime += minutes;
  }
  
  finalTime += ":";
  
  if (seconds < 10) {
    finalTime += "0";
    finalTime += seconds;
  }
  else {
    finalTime += seconds;
  }
  
  return finalTime;
}


String getDS3231Date() {
  String finalDate = "";
  int dateDay = getMonthDay();
  int months = getMonth();
  int years = getYear();
  if (dateDay < 10) {
    finalDate += "0";
    finalDate += dateDay;
  }
  else {
    finalDate += dateDay;
  }
  finalDate += "/";
  if (months < 10) {
    finalDate += "0";
    finalDate += months;
  }
  else {
    finalDate += months;
  }
  finalDate += "/";
  if (years < 10) {
    finalDate += "0";
    finalDate += years;
  }
  else {
    finalDate += years;
  }
  return finalDate;
}


//setter functions
int setHour(uint8_t currHour) {
  Wire.begin();
  Wire.beginTransmission(ADDRESS);
  Wire.write(0x2);
  uint8_t fullHour = binaryToBCD(currHour) | (RTC.hours & 0b11100000);
  Wire.write(fullHour);
  if (!Wire.endTransmission()) {
    return -1;
  }
  return 0;
}


int setMinutes(uint8_t currMin) {
  Wire.begin();
  Wire.beginTransmission(ADDRESS);
  Wire.write(0x1);
  Wire.write(binaryToBCD(currMin));
  if (!Wire.endTransmission()) {
    return -1;
  }
  return 0;
}


int setSeconds(uint8_t currSec) {
  Wire.begin();
  Wire.beginTransmission(ADDRESS);
  Wire.write(0x0);
  Wire.write(binaryToBCD(currSec));
  if (!Wire.endTransmission()) {
    return -1;
  }
  return 0;
}


int setMonthDay(uint8_t currDateDay) {
  Wire.begin();
  Wire.beginTransmission(ADDRESS);
  Wire.write(0x4);
  Wire.write(binaryToBCD(currDateDay));
  if (!Wire.endTransmission()) {
    return -1;
  }
  setDoW(currDateDay, getMonth(), getYear());
  return 0;
}


int setMonth(uint8_t currMonth) {
  Wire.begin();
  Wire.beginTransmission(ADDRESS);
  Wire.write(0x5);
  Wire.write(binaryToBCD(currMonth) & 0b00011111);
  if (!Wire.endTransmission()) {
    return -1;
  }
  setDoW(getMonthDay(), currMonth, getYear());
  return 0;
}


int setYear(int currYear) {
  Wire.begin();
  Wire.beginTransmission(ADDRESS);
  Wire.write(0x6);
  Wire.write(binaryToBCD(currYear % 100));
  if (!Wire.endTransmission()) {
    return -1;
  }
  setDoW(getMonthDay(), getMonth(), currYear);
  return 0;
}


int setFullTime(uint8_t currHour, uint8_t currMin, uint8_t currSec) {
  setHour(currHour);
  setMinutes(currMin);
  setSeconds(currSec);
  return 0;
}


int setFullDate(int currDay, int currMonth, int currYear) {
  setMonthDay(currDay);
  setMonth(currMonth);
  setYear(currYear);
  setDoW(currDay, currMonth, currYear);
  return 0;
}


int getDoW(int d, int m, int y) {
  static int t[] = { 0, 3, 2, 5, 0, 3,
                     5, 1, 4, 6, 2, 4
                   };
  y -= m < 3;
  return ( y + y / 4 - y / 100 +
           y / 400 + t[m - 1] + d) % 7;
}


int setDoW(int d, int m, int y) {
  Wire.begin();
  Wire.beginTransmission(ADDRESS);
  Wire.write(0x3);
  Wire.write(binaryToBCD(getDoW(d, m, y)));
  if (!Wire.endTransmission()) {
    return -1;
  }
  return 0;
}
