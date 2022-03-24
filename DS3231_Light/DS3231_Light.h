#ifndef DS3231_LIGHT_H
#define DS3231_LIGHT_H
#include <Arduino.h>

#define SECOND 1000
#define ADDRESS 0x68

//No century or alarm support in this library!

typedef struct DS3231_Light{
  uint8_t secondsData;
  uint8_t minutesData;
  uint8_t hourData;
  
}DS3231_Light;


//number control
int BCDToBinary(uint8_t number);
uint8_t binaryToBCD(uint8_t number);

//read registers
void readRTC();//reads current value of RTC registers

//getter functions

int extractHour();//gets current hour
int extractMinutes();//gets current minutes
int extractSeconds();//gets current seconds
int extractMonth(uint8_t number);
int extractYear(uint8_t number);

//setter functions
void setHour(uint8_t currHour);
void setMinutes(uint8_t currMin);
void setSeconds(uint8_t currSec);
void setMonth(uint8_t currMonth);
void setYear(int currYear);

//print functions
String prettyPrintTime();//TODO

#endif
