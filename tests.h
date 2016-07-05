/*
 * Copyright (c) 2016 by Stefano Speretta <s.speretta@tudelft.nl>
 *
 * I2CTester_checkout: this is an application designed to test the 
 * functionality of the I2C Tester setup. The setup includes several 
 * devices on different boards to perform a long duration test on 
 * the hardware and software implementation. It is designed to use 
 * Energia (the Arduino port for MSP microcontrollers) on an MSP432.
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License 
 * version 3, both as published by the Free Software Foundation.
 *
 */
 
#ifndef __TESTS_H__
#define __TESTS_H__

#include "Energia.h"
#include <DWire.h>
#include <DSerial.h>
#include <I2CScanner.h>
#include <INA226.h>
#include <MAX1237.h>
#include <PCA9550.h>

#define BUS1       24
#define BUS2        5
#define BUS3        8   // the pin here should be 25 but the pin is burnt, so it was rewired to pin 8
#define BUS4        6
#define BUS5       26
#define BUS6       27
   
#define SHUNT_RESISTOR 0.04

extern DWire wire;
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
