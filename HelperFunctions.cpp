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
 
#include "HelperFunctions.h"

/**
 *
 *   Scan the I2C bus and list the available devices.
 *   The available addresses are printed to the Serial console
 *   
 *   Returns:
 *   unsigned char        number of devices found
 *
 */
unsigned char scanBus()
{
    unsigned char devices = 0;
    serial.println("Scanning bus... ");
    for(unsigned char address = 1; address < 126; address++ )
    {
        unsigned char count = wire.requestFrom(address, (unsigned char)1);    // request 1 byte
        
        if (count != 0) 
        {
            devices++;
            serial.print("Found Address 0x");
            if (address < 15) 
            {
                serial.print('0');
            }
            serial.print(address, HEX);
            serial.println();
        }
        delay(5);
    }   
    if (devices == 0)
    {
        serial.println("No device found");
    }
    serial.println("Scan completed");
    
    return devices;
}

