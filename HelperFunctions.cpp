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
        //wire.beginTransmission(address);
        unsigned char count = wire.requestFrom(address, (unsigned char)1);    // request 1 byte
        //wire.endTransmission();
        
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

