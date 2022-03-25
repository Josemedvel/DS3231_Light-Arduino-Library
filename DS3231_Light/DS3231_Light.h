#ifndef DS3231_LIGHT_H
#define DS3231_LIGHT_H
#include <Arduino.h>

#define SECOND 1000
#define ADDRESS 0x68
const char  weekDayNames [7][10] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
//No alarm support in this library!

typedef struct DS3231_Light {
  uint8_t seconds;
  uint8_t minutes;
  uint8_t hours;
  uint8_t weekDay;
  uint8_t dateDay;
  uint8_t months;
  uint8_t years;
  String weekDayName;

} DS3231_Light;


//number control
int BCDToBinary(uint8_t number);//converts Binary Coded Decimal to binary
uint8_t binaryToBCD(uint8_t number);//converts binary to Binary Coded Decimal

//read registers
int readRTC();//reads current value of RTC registers

//getter functions

int getHour();//gets current hour
int getMinutes();//gets current minutes
int getSeconds();//gets current seconds
int getWeekDay();//gets current weekday
String getWeekDayName();//gets current weekday name
int getMonthDay();//gets current date day
int getMonth();//gets current month
int getYear();//gets current year
int getCentury();//gets current century
String getDS3231Time();//gets complete time
String getDS3231Date();//gets complete date

//setter functions
int setHour(uint8_t currHour);//sets current hour
int setMinutes(uint8_t currMin);//sets current minutes
int setSeconds(uint8_t currSec);//sets current seconds
int setMonth(uint8_t currMonth);//sets current month
int setMonthDay(uint8_t currDateDay);//sets current date day
int setYear(int currYear);//sets current year
int setFullTime(uint8_t currHour, uint8_t currMin, uint8_t currSec); //sets full time
int setFullDate(int currDay, int currMonth, int currYear);//sets full date

//day of the week calculation
int getDoW(int d, int m, int y);// returns weekday based on date (gregorian calendar)
int setDoW(int d, int m, int y);//sets the new day of the week after a change in the calendar occurs
#endif
