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
 
#include <DWire.h>
#include <DSerial.h>
#include "tests.h"

#define TEST_BUS_1        true
#define TEST_BUS_4        true
#define TEST_BUS_6        true

DWire wire;
DSerial serial;

void setup()
{
  // Initialize I2C master
  wire.setStandardMode();
  wire.begin();
  
  // initialize debug UART
  serial.begin();

  // wait to make sure the UART is initialized
  delay(10);
  
  // initialize the GPIOs used to control the power buses
  initTests();
}

void loop()
{
  serial.println();
  serial.println("-----------------------------------------------------");
  serial.println("---------    I2CTester Checkout Software    ---------");
  serial.println("-----------------------------------------------------");
  serial.println();
  
  // run all the tests in sequence
  // All busses off, list if any device is on
  Test1();
  
  if (TEST_BUS_4)
  {
      // check if there are 2 devices
      Test2();
  
      // check if the INA226 works 
      Test3();
  
      // check if the MAX1237 works 
      Test4();
  }
  
  if (TEST_BUS_6)
  {
      // check if there are 2 devices
      Test5();

      // check if the INA226 works 
      Test6();
  
      // check if the blinker is blinking and if the switch turns ON and OFF
      Test7();
  }
  
  if (TEST_BUS_1)
  {
      Test8();
      
      Test9();
  }
  
  //delay(2000);
}
