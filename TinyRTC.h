/*
    TinyRTC.h - Library for using RTC DS3231 with AtTiny85.
    Note that you need to use Spence Konde's ATTiny Core and TinyI2CMaster library for these routines to work.
    
    Created by Hernán Rodríguez - hernan.rod.98@gmail.com - March 15, 2021.
    
    CC BY 4.0
    Licensed under a Creative Commons Attribution 4.0 International license: 
    http://creativecommons.org/licenses/by/4.0/
*/

#ifndef TinyRTC_h
#define TinyRTC_h

#include "Arduino.h"
#include "TinyI2CMaster.h"

#define RTC_ADDRESS 0x68

#define ALARM_1 true
#define ALARM_2 false

#define ALARM_PER_SEC                   0
#define ALARM_SEC_MATCH                 1
#define ALARM_MIN_SEC_MATCH             2
#define ALARM_HOUR_MIN_SEC_MATCH        3
#define ALARM_DAY_HOUR_MIN_SEC_MATCH    4
#define ALARM_DATE_HOUR_MIN_SEC_MATCH   5

#define ALARM_PER_MIN                   6
#define ALARM_MIN_MATCH                 7
#define ALARM_HOUR_MIN_MATCH            8
#define ALARM_DAY_HOUR_MIN_MATCH        9
#define ALARM_DATE_HOUR_MIN_MATCH       10

class TinyRTC{
    public:
        TinyRTC();
        void init();

        void setTime(byte secs, byte mins, byte hrs, byte day, byte day_month, byte month, byte year);
        void setSeconds(byte secs);
        void setMinutes(byte mins);
        void setHours(byte hrs);
        void setDayWeek(byte day);
        void setDayMonth(byte day);
        void setMonth(byte month);
        void setYear(byte year);

        byte getSeconds();
        byte getMinutes();
        byte getHours();
        byte getDayWeek();
        byte getDayMonth();
        byte getMonth();
        byte getYear();

        void initAlarm(bool n);
        void setAlarm(bool n, byte segs, byte mins, byte hrs, byte day);
        void customAlarm(bool n, byte kind);
        void clearAlarm(bool n);

    private:
        byte readByte(byte dir);
        void writeByte(byte dir, byte data);
        byte bcdToDec(byte val);
        byte decToBcd(byte val);
};

extern TinyRTC TinyRtc;

#endif