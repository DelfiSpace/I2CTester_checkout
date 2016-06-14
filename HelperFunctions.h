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
 
#ifndef _HELPERFUNCTIONS_H__
#define _HELPERFUNCTIONS_H__

#include "Energia.h"
#include <DWire.h>
#include <DSerial.h>

extern DWire wire;
extern DSerial serial;

unsigned char scanBus();

#endif
