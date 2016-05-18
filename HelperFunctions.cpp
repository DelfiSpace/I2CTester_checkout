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
    Serial.println("Scanning bus... ");
    for(unsigned char address = 1; address < 127; address++ )
    {
        Wire.beginTransmission(address);
        unsigned char count = Wire.requestFrom(address, (unsigned char)1);    // request 1 byte
        Wire.endTransmission();
        
        if (count != 0) 
        {
            devices++;
            Serial.print("Found Address 0x");
            if (address < 15) 
            {
                Serial.print('0');
            }
            Serial.println(address,HEX);
        }
        delay(5);
    }   
    if (devices == 0)
    {
        Serial.println("No device found");
    }
    Serial.println("Scan completed");
    
    return devices;
}

