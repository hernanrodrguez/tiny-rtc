/*
    TinyRTC.cpp - Library for using RTC DS3231 with AtTiny85.
    Note that you need to use Spence Konde's ATTiny Core and TinyI2CMaster library for these routines to work.
    
    Created by Hernán Rodríguez - hernan.rod.98@gmail.com - March 15, 2021.
    
    CC BY 4.0
    Licensed under a Creative Commons Attribution 4.0 International license: 
    http://creativecommons.org/licenses/by/4.0/
*/

#include "TinyRTC.h"
#include "Arduino.h"
#include "TinyI2CMaster.h"

TinyRTC::TinyRTC(){}

void TinyRTC::init(){
    TinyI2C.init(); 
}

void TinyRTC::setTime(byte secs, byte mins, byte hrs, byte day, byte day_month, byte month, byte year){
    writeByte(0x00, decToBcd(secs));  
    writeByte(0x01, decToBcd(mins)); 
    writeByte(0x02, decToBcd(hrs));  
    writeByte(0x03, decToBcd(day));  
    writeByte(0x04, decToBcd(day_month));  
    writeByte(0x05, decToBcd(month));  
    writeByte(0x06, decToBcd(year));  
}

void TinyRTC::setSeconds(byte secs){
    writeByte(0x00, decToBcd(secs)); 
}

void TinyRTC::setMinutes(byte mins){
    writeByte(0x01, decToBcd(mins)); 
}

void TinyRTC::setHours(byte hrs){
    writeByte(0x02, decToBcd(hrs)); 
}

void TinyRTC::setDayWeek(byte day){
    writeByte(0x03, decToBcd(day)); 
}

void TinyRTC::setDayMonth(byte day){
    writeByte(0x04, decToBcd(day)); 
}

void TinyRTC::setMonth(byte month){
    writeByte(0x05, decToBcd(month)); 
}

void TinyRTC::setYear(byte year){
    writeByte(0x06, decToBcd(year)); 
}

byte TinyRTC::getSeconds(){
    return bcdToDec(readByte(0x00));
}

byte TinyRTC::getMinutes(){
    return bcdToDec(readByte(0x01));
}

byte TinyRTC::getHours(){
    return bcdToDec(readByte(0x02));
}

byte TinyRTC::getDayWeek(){
    return bcdToDec(readByte(0x03));
}

byte TinyRTC::getDayMonth(){
    return bcdToDec(readByte(0x04));
}

byte TinyRTC::getMonth(){
    return bcdToDec(readByte(0x05));
}

byte TinyRTC::getYear(){
    return bcdToDec(readByte(0x06));
}

void TinyRTC::initAlarm(bool n){
    byte aux = readByte(0x0E);

    if(n) // alarm 1
        aux = aux | 0b00000101; // set INTCN and A1IE to 1
    else // alarm 2
        aux = aux | 0b00000110; // set INTCN and A2IE to 1
    
    writeByte(0x0E, aux);

    clearAlarm(n);
}

void TinyRTC::setAlarm(bool n, byte segs, byte mins, byte hrs, byte day){ // only for day of week, not for date
    if(n){ // alarm 1
        writeByte(0x07, decToBcd(segs));  
        writeByte(0x08, decToBcd(mins)); 
        writeByte(0x09, decToBcd(hrs));  
        writeByte(0x0A, decToBcd(day)); 
    } else { // alarm 2 
        writeByte(0x0B, decToBcd(mins)); 
        writeByte(0x0C, decToBcd(hrs));  
        writeByte(0x0D, decToBcd(day));
    }
}

void TinyRTC::customAlarm(bool n, byte kind){
    byte aux;
    if(n){ // alarm 1
        switch(kind){
            case ALARM_PER_SEC:
                aux = readByte(0x07); // A1M1
                aux = aux | 0b10000000;
                writeByte(0x07, aux);

                aux = readByte(0x08); // A1M2
                aux = aux | 0b10000000;
                writeByte(0x08, aux);

                aux = readByte(0x09); // A1M3
                aux = aux | 0b10000000;
                writeByte(0x09, aux);

                aux = readByte(0x0A); // A1M4
                aux = aux | 0b10000000;
                writeByte(0x0A, aux);

                break;

            case ALARM_SEC_MATCH:
                aux = readByte(0x07); // A1M1
                aux = aux & 0b01111111;
                writeByte(0x07, aux);

                aux = readByte(0x08); // A1M2
                aux = aux | 0b10000000;
                writeByte(0x08, aux);

                aux = readByte(0x09); // A1M3
                aux = aux | 0b10000000;
                writeByte(0x09, aux);

                aux = readByte(0x0A); // A1M4
                aux = aux | 0b10000000;
                writeByte(0x0A, aux);

                break;

            case ALARM_MIN_SEC_MATCH:
                aux = readByte(0x07); // A1M1
                aux = aux & 0b01111111;
                writeByte(0x07, aux);

                aux = readByte(0x08); // A1M2
                aux = aux & 0b01111111;
                writeByte(0x08, aux);

                aux = readByte(0x09); // A1M3
                aux = aux | 0b10000000;
                writeByte(0x09, aux);

                aux = readByte(0x0A); // A1M4
                aux = aux | 0b10000000;
                writeByte(0x0A, aux);

                break;

            case ALARM_HOUR_MIN_SEC_MATCH:
                aux = readByte(0x07); // A1M1
                aux = aux & 0b01111111;
                writeByte(0x07, aux);

                aux = readByte(0x08); // A1M2
                aux = aux & 0b01111111;
                writeByte(0x08, aux);

                aux = readByte(0x09); // A1M3
                aux = aux & 0b01111111;
                writeByte(0x09, aux);

                aux = readByte(0x0A); // A1M4
                aux = aux | 0b10000000;
                writeByte(0x0A, aux);

                break;

            case ALARM_DAY_HOUR_MIN_SEC_MATCH:
                aux = readByte(0x07); // A1M1
                aux = aux & 0b01111111;
                writeByte(0x07, aux);

                aux = readByte(0x08); // A1M2
                aux = aux & 0b01111111;
                writeByte(0x08, aux);

                aux = readByte(0x09); // A1M3
                aux = aux & 0b01111111;
                writeByte(0x09, aux);

                aux = readByte(0x0A); 
                aux = aux & 0b01111111; // A1M4
                aux = aux | 0b01000000; // DY
                writeByte(0x0A, aux);

                break; 

            case ALARM_DATE_HOUR_MIN_SEC_MATCH:
                aux = readByte(0x07); // A1M1
                aux = aux & 0b01111111;
                writeByte(0x07, aux);

                aux = readByte(0x08); // A1M2
                aux = aux & 0b01111111;
                writeByte(0x08, aux);

                aux = readByte(0x09); // A1M3
                aux = aux & 0b01111111;
                writeByte(0x09, aux);

                aux = readByte(0x0A); 
                aux = aux & 0b00111111; // A1M4 - DT
                writeByte(0x0A, aux);

                break;       
        }
    } else { // alarm 2
        switch(kind){
            case ALARM_PER_MIN:
                aux = readByte(0x0B); // A2M2
                aux = aux | 0b10000000;
                writeByte(0x0B, aux);

                aux = readByte(0x0C); // A2M3
                aux = aux | 0b10000000;
                writeByte(0x0C, aux);

                aux = readByte(0x0D); // A2M4
                aux = aux | 0b10000000;
                writeByte(0x0D, aux);

                break;

            case ALARM_MIN_MATCH:
                aux = readByte(0x0B); // A2M2
                aux = aux & 0b01111111;
                writeByte(0x0B, aux);

                aux = readByte(0x0C); // A2M3
                aux = aux | 0b10000000;
                writeByte(0x0C, aux);

                aux = readByte(0x0D); // A2M4
                aux = aux | 0b10000000;
                writeByte(0x0D, aux);

                break;

            case ALARM_HOUR_MIN_MATCH:
                aux = readByte(0x0B); // A2M2
                aux = aux & 0b01111111;
                writeByte(0x0B, aux);

                aux = readByte(0x0C); // A2M3
                aux = aux & 0b01111111;
                writeByte(0x0C, aux);

                aux = readByte(0x0D); // A2M4
                aux = aux | 0b10000000;
                writeByte(0x0D, aux);

                break;

            case ALARM_DAY_HOUR_MIN_MATCH:
                aux = readByte(0x0B); // A2M2
                aux = aux & 0b01111111;
                writeByte(0x0B, aux);

                aux = readByte(0x0C); // A2M3
                aux = aux & 0b01111111;
                writeByte(0x0C, aux);

                aux = readByte(0x0D); 
                aux = aux & 0b01111111; // A2M4
                aux = aux | 0b01000000; // DY
                writeByte(0x0D, aux);

                break;

            case ALARM_DATE_HOUR_MIN_MATCH:
                aux = readByte(0x0B); // A2M2
                aux = aux & 0b01111111;
                writeByte(0x0B, aux);

                aux = readByte(0x0C); // A2M3
                aux = aux & 0b01111111;
                writeByte(0x0C, aux);

                aux = readByte(0x0D); 
                aux = aux & 0b00111111; // A2M4 - DT
                writeByte(0x0D, aux);

                break;   
        }
    }
}

void TinyRTC::clearAlarm(bool n){
    byte aux = readByte(0x0F);

    if(n) // alarm 1
        aux = aux & 0b11111110; // clear A1F
    else // alarm 2
        aux = aux & 0b11111101; // clear A2F

    writeByte(0x0F, aux);
}

byte TinyRTC::readByte(byte dir){
    byte aux;

    TinyI2C.start(RTC_ADDRESS, 0);
    TinyI2C.write(dir);
    TinyI2C.restart(RTC_ADDRESS, 1);
    aux = TinyI2C.read();
    TinyI2C.stop();
  
    return aux;
}

void TinyRTC::writeByte(byte dir, byte data){
    TinyI2C.start(RTC_ADDRESS, 0);
    TinyI2C.write(dir);
    TinyI2C.write(data);
    TinyI2C.stop();
}

byte TinyRTC::bcdToDec(byte val){
    return((val/16*10) + (val%16));
}

byte TinyRTC::decToBcd(byte val){
    return ((val/10*16) + (val%10));
}

TinyRTC TinyRtc = TinyRTC(); // preinstantiate object