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
void readRTC() {
  Wire.begin();
  Wire.beginTransmission(ADDRESS);
  Wire.write(0x00);//first register
  Wire.requestFrom(ADDRESS, 3);//change in the future for month and year
  RTC.secondsData = Wire.read();
  RTC.minutesData = Wire.read();
  RTC.hourData = Wire.read();
  if (!Wire.endTransmission() == 0) {
    Serial.println("Reading error");
  }
}

//getter functions

int extractHour() {
  if ((RTC.hourData & 0b0100000) == 0) { //check 12 hours mode
    //Serial.println("We are in 12 hours mode");
    return BCDToBinary(RTC.hourData & 0b00011111);
  }
  else { //We are in 24 hours mode
    //Serial.println("We are in 24 hours mode");
    return BCDToBinary(RTC.hourData & 0b00111111);
  }
}

int extractMinutes() {
  return BCDToBinary(RTC.minutesData);
}

int extractSeconds() {
  return BCDToBinary(RTC.secondsData);
}

int extractMonth(uint8_t number);
int extractYear(uint8_t number);

//setter functions
void setHour(uint8_t currHour);
void setMinutes(uint8_t currMin);
void setSeconds(uint8_t currSec);
void setMonth(uint8_t currMonth);
void setYear(int currYear);

//print functions
String prettyPrintTime(){//TODO
  String finalTime = "";
  if(RTC.hourData < 10){
    finalTime += "0"+(int)RTC.hourData;
  }
  else{
    finalTime += (int)RTC.hourData;
  }
  finalTime += ":";
  if(RTC.minutesData < 10){
    finalTime += "0"+(int)RTC.minutesData;
  }
  else{
    finalTime += (int)RTC.minutesData;
  }
  finalTime += ":";
  if(RTC.secondsData < 10){
    finalTime += "0"+(int)RTC.secondsData;
  }
  else{
    finalTime += (int)RTC.secondsData;
  }
  Serial.println(finalTime);
  return finalTime;
}
