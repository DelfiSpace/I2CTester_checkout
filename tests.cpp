/*
 * Copyright (c) 2016 by Stefano Speretta <s.speretta@tudelft.nl>
 *
 * I2CTester_checkout: this is an application designed to test the 
 * functionality of he I2C Tester setup. The setuo includes several 
 * devices on different boards to perform a long duration test on 
 * the hardware and software implementation. It is designed to use 
 * Energia (the Arduino port for MSP microcontrollers) on an MSP432.
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License 
 * version 3, both as published by the Free Software Foundation.
 *
 */
 
#include "tests.h"

void initTests()
{
    // set-up power bus control pins
    
    // first turn all buses off to avoid glitches
    switchOFF();
    
    // then set the pin direction to output
    pinMode(BUS1, OUTPUT);
    pinMode(BUS2, OUTPUT);
    pinMode(BUS3, OUTPUT);
    pinMode(BUS4, OUTPUT);
    pinMode(BUS5, OUTPUT);
    pinMode(BUS6, OUTPUT);
}

void switchOFF()
{
    // ensure that all power buses are OFF
    digitalWrite(BUS1, LOW);
    digitalWrite(BUS2, LOW);
    digitalWrite(BUS3, LOW);
    digitalWrite(BUS4, LOW);
    digitalWrite(BUS5, LOW);
    digitalWrite(BUS6, LOW);
}


/**
 *
 *   Test 1: check that no device is accessible via I2C when the power buses are OFF.
 *   This is used to verify that no sneak circuit is present on the bus.
 *
 */
void Test1()
{
    beginTest();
    
    // ensure that all power buses are OFF
    switchOFF();
    
    // ensure the system turned off
    delay(10);
    
    // scan the bus and count the available devices
    unsigned char num = scanBus();
    showResult(num == 0);
}

/**
 *
 *   Test 2: check that only 2 devices are accessible via I2C when only power bus 4 is ON.
 *   This is used to verify that no sneak circuit is present and that bus 1 is correctly working.
 *
 */
void Test2()
{
    beginTest();
    
    // ensure that all power buses are OFF but number 4
    switchOFF();
    digitalWrite(BUS4, HIGH);
    
    // ensure the system turned on
    delay(10);
    
    // scan the bus and count the available devices
    unsigned char num = scanBus();
    showResult(num == 2);
    
    // turn all the buses off
    switchOFF();
}

/**
 *
 *   Test 3: check that the INA226 on bus 4 works properly.
 *   This is used to verify that no sneak circuit is present and that bus 1 is correctly working.
 *
 */
void Test3()
{
    beginTest();
 
    INA226 ina(wire, 0x40);
 
    // ensure that all power buses are OFF but number 1
    switchOFF();
    digitalWrite(BUS4, HIGH);
    
    // ensure the system turned on
    delay(10);
    
    // set the shunt resistor for the INA on bus 1
    ina.setShuntResistor(SHUNT_RESISTOR);
    
    // ensure enough time for the INA to sample the current once
    delay(10);
    
    if (ina.ping())
    {
        serial.println("INA226 present");
        
        // read the telemetry from the INA226
        unsigned short v = ina.getVoltage();
        signed short i = ina.getCurrent();
        unsigned short p = ina.getPower();
   
        serial.print("Voltage: ");
        serial.print(v, DEC);
        serial.println(" mV");
 
        serial.print("Current: ");
        serial.print(i, DEC);
        serial.println(" mA");
 
        serial.print("Power ");
        serial.print(p, DEC);
        serial.println(" mW");
   
        // check that the values are within the correct range
        showResult((v > 3500) && (v < 5500) && (i > 10) && (i < 20) && (p > 50) && (p < 70));
    }
    else
    {
        serial.println("INA226 not present");
        showResult(false);
    }
    
    // turn all the buses off
    switchOFF();
}

/**
 *
 *   Test 4: check that the MAX1237 on bus 4 works properly.
 *   This is used to verify that no sneak circuit is present and that bus 1 is correctly working.
 *
 */
void Test4()
{
    beginTest();
 
    MAX1237 adc(wire);
 
    // ensure that all power buses are OFF but number 1
    switchOFF();
    digitalWrite(BUS4, HIGH);
    
    // ensure the system turned on
    delay(10);
    
    adc.writeRegister(0x80 | 0x02 | (0x05 << 4));
    adc.writeRegister(CS2 | SCAN3 | 1);
  
    unsigned short val = adc.readSingleChannel() >> 1; 
    serial.print("ADC: ");
    serial.print(val, DEC);
    serial.println(" mV");
    
    showResult((val > 1500) && (val < 1700));
    
    // turn all the buses off
    switchOFF();
}

/**
 *
 *   Test 5: check that only 2 devices are accessible via I2C when only power bus 6 is ON.
 *   This is used to verify that no sneak circuit is present and that bus 1 is correctly working.
 *
 */
void Test5()
{
    beginTest();
    
    // ensure that all power buses are OFF but number 6
    switchOFF();
    digitalWrite(BUS6, HIGH);
    
    // ensure the system turned on
    delay(10);
    
    // scan the bus and count the available devices
    unsigned char num = scanBus();
    showResult(num == 2);
    
    // turn all the buses off
    switchOFF();
}

/**
 *
 *   Test 6: check that the INA226 on bus 6 works properly.
 *   This is used to verify that no sneak circuit is present and that bus 1 is correctly working.
 *
 */
void Test6()
{
    beginTest();
    
    INA226 ina(wire, 0x45);
    PCA9550 blinker(wire, 0x61);
        
    // ensure that all power buses are OFF but number 6
    switchOFF();
    digitalWrite(BUS6, HIGH);
    
    // ensure the system turned on
    delay(10);
    
    // switch the power load OFF
    blinker.setOutput(0, 0);
    
    // set the shunt resistor for the INA on bus 6
    ina.setShuntResistor(SHUNT_RESISTOR);
    
    // ensure enough time for the INA to sample the current once
    delay(10);
    
    if (ina.ping())
    {
        serial.println("INA226 present");
        
        // read the telemetry from the INA226
        unsigned short v = ina.getVoltage();
        signed short i = ina.getCurrent();
        unsigned short p = ina.getPower();
   
        serial.print("Voltage: ");
        serial.print(v, DEC);
        serial.println(" mV");
 
        serial.print("Current: ");
        serial.print(i, DEC);
        serial.println(" mA");
 
        serial.print("Power ");
        serial.print(p, DEC);
        serial.println(" mW");
   
        // check that the values are within the correct range
        showResult((v > 3500) && (v < 5500) && (i > 0) && (i < 10) && (p > 10) && (p < 30));
    }
    else
    {
        serial.println("INA226 not present");
        showResult(false);
    }
    
    // turn all the buses off
    switchOFF();
}

/**
 *
 *   Test 7: check that the PCA9550 on bus 6 works properly.
 *   This is used to verify that no sneak circuit is present and that bus 1 is correctly working.
 *
 */
void Test7()
{
    beginTest();
    
    INA226 ina(wire, 0x45);
    PCA9550 blinker(wire, 0x61);
    
    // ensure that all power buses are OFF but number 6
    switchOFF();
    digitalWrite(BUS6, HIGH);
    
    // ensure the system turned on
    delay(10);
    
    // switch the power load OFF
    blinker.setOutput(0, 0);
    
    // set the shunt resistor for the INA on bus 6
    ina.setShuntResistor(SHUNT_RESISTOR);
    
    delay(10);
    
    if (ina.ping())
    {
        serial.println("INA226 present");
        
        // read the telemetry from the INA226
        signed short i1 = ina.getCurrent();

        serial.print("Current OFF: ");
        serial.print(i1, DEC);
        serial.println(" mA");
 
        // turn the power load ON
        blinker.setOutput(0, 1);
    
        delay(200);
        
        signed short i2 = ina.getCurrent();
        
        serial.print("Current ON: ");
        serial.print(i2, DEC);
        serial.println(" mA");

        // turn the power load OFF
        blinker.setOutput(0, 0);
        
        showResult((i1 < 20) && (i2 > 850));
    }
    else
    {
        serial.println("INA226 not present");
        showResult(false);
    }
    
    // turn all the buses off
    switchOFF();
}

/**
 *
 *   Test 8: check that only 2 devices are accessible via I2C when only power bus 1 is ON.
 *   This is used to verify that no sneak circuit is present and that bus 1 is correctly working.
 *
 */
void Test8()
{
    beginTest();
    
    // ensure that all power buses are OFF but number 1
    switchOFF();
    digitalWrite(BUS1, HIGH);
    
    // ensure the system turned on
    delay(10);
    
    // scan the bus and count the available devices
    unsigned char num = scanBus();
    showResult(num == 2);
    
    // turn all the buses off
    switchOFF();
}

/**
 *
 *   Test 9: check that the PCA9550 on bus 6 works properly.
 *   This is used to verify that no sneak circuit is present and that bus 1 is correctly working.
 *
 */
void Test9()
{
    beginTest();
    
    INA226 ina(wire, 0x44);
    PCA9550 blinker(wire, 0x60);
    
    // ensure that all power buses are OFF but number 6
    switchOFF();
    digitalWrite(BUS1, HIGH);
    
    // ensure the system turned on
    delay(10);
    
    // switch the power load OFF
    blinker.setOutput(0, 0);
    
    // set the shunt resistor for the INA on bus 6
    ina.setShuntResistor(SHUNT_RESISTOR);
    
    delay(10);
    
    if (ina.ping())
    {
        serial.println("INA226 present");
        
        // read the telemetry from the INA226
        signed short i1 = ina.getCurrent();

        serial.print("Current OFF: ");
        serial.print(i1, DEC);
        serial.println(" mA");
 
        // turn the power load ON
        blinker.setOutput(0, 1);
    
        delay(200);
        
        signed short i2 = ina.getCurrent();
        
        serial.print("Current ON: ");
        serial.print(i2, DEC);
        serial.println(" mA");

        // turn the power load OFF
        blinker.setOutput(0, 0);
        
        showResult((i1 < 20) && (i2 > 850));
    }
    else
    {
        serial.println("INA226 not present");
        showResult(false);
    }
    
    // turn all the buses off
    switchOFF();
}

