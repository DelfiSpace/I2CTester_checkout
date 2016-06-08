#ifndef __TESTS_H__
#define __TESTS_H__

#include "Energia.h"
#include <DWire.h>
#include <DSerial.h>
#include <INA226.h>
#include <MAX1237.h>
#include <PCA9550.h>
#include "HelperFunctions.h"

#define BUS1       24
#define BUS2        5
#define BUS3        8   // the pin here should be 25 but the pin is burnt, so it was rewired to pin 8
#define BUS4        6
#define BUS5       26
#define BUS6       27
   
#define SHUNT_RESISTOR 0.05

extern DSerial serial;

#define beginTest()                         \
{                                           \
    serial.print("############## ");        \
    serial.print(__FUNCTION__);             \
    serial.println(" ##############");      \
}

#define showResult(condition)               \
{                                           \
    serial.print("########## Result: ");    \
    if (condition)                          \
    {                                       \
        serial.print("PASS");               \
    }                                       \
    else                                    \
    {                                       \
        serial.print("FAIL");               \
    }                                       \
    serial.println(" ###########");         \
    serial.println();                       \
}



void Test1();
void Test2();
void Test3();
void Test4();
void Test5();
void Test6();
void Test7();
void Test8();
void Test9();

void initTests();  
void switchOFF();

#endif
