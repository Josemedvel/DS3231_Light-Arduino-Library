#ifndef DS3231_LIGHT_H
#define DS3231_LIGHT_H
#include <Arduino.h>
int BCDToBinary(uint8_t number);
int extractHours(uint8_t number);
#endif
