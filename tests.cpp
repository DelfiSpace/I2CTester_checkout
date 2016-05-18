#include "tests.h"

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
 *   Test 2: check that only 2 devices are accessible via I2C when only power bus 1 is ON.
 *   This is used to verify that no sneak circuit is present and that bus 1 is correctly working.
 *
 */
void Test2()
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
 *   Test 3: check that the INA226 on bus 1 works properly.
 *   This is used to verify that no sneak circuit is present and that bus 1 is correctly working.
 *
 */
void Test3()
{
    beginTest();
 
    INA226 ina_bus1(0x40);
 
    // ensure that all power buses are OFF but number 1
    switchOFF();
    digitalWrite(BUS1, HIGH);
    
    // ensure the system turned on
    delay(10);
    
    // set the shunt resistor for the INA on bus 1
    ina_bus1.setShuntResistor(SHUNT_RESISTOR);
    
    // ensure enough time for the INA to sample the current once
    delay(10);
    
    if (ina_bus1.ping())
    {
        Serial.println("INA226 present");
        
        // read the telemetry from the INA226
        unsigned short v = ina_bus1.getVoltage();
        signed short i = ina_bus1.getCurrent();
        unsigned short p = ina_bus1.getPower();
   
        Serial.print("Voltage: ");
        Serial.print(v, DEC);
        Serial.println(" mV");
 
        Serial.print("Current: ");
        Serial.print(i, DEC);
        Serial.println(" mA");
 
        Serial.print("Power ");
        Serial.print(p, DEC);
        Serial.println(" mW");
   
        // check that the values are within the correct range
        showResult((v > 3500) && (v < 5500) && (i > 10) && (i < 20) && (p > 50) && (p < 70));
    }
    else
    {
        Serial.println("INA226 not present");
        showResult(false);
    }
    
    // turn all the buses off
    switchOFF();
}

/**
 *
 *   Test 4: check that the MAX1237 on bus 1 works properly.
 *   This is used to verify that no sneak circuit is present and that bus 1 is correctly working.
 *
 */
void Test4()
{
    beginTest();
 
    MAX1237 adc_bus1;
 
    // ensure that all power buses are OFF but number 1
    switchOFF();
    digitalWrite(BUS1, HIGH);
    
    // ensure the system turned on
    delay(10);
    
    adc_bus1.writeRegister(0x80 | 0x02 | (0x05 << 4));
    adc_bus1.writeRegister(CS2 | SCAN3 | 1);
  
    unsigned short val = adc_bus1.readSingleChannel() >> 1; 
    Serial.print("ADC: ");
    Serial.print(val, DEC);
    Serial.println(" mV");
    
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
    
    INA226 ina_bus6(0x45);
    
    // ensure that all power buses are OFF but number 6
    switchOFF();
    digitalWrite(BUS6, HIGH);
    
    // ensure the system turned on
    delay(10);
    
    // set the shunt resistor for the INA on bus 6
    ina_bus6.setShuntResistor(SHUNT_RESISTOR);
    
    // ensure enough time for the INA to sample the current once
    delay(10);
    
    if (ina_bus6.ping())
    {
        Serial.println("INA226 present");
        
        // read the telemetry from the INA226
        unsigned short v = ina_bus6.getVoltage();
        signed short i = ina_bus6.getCurrent();
        unsigned short p = ina_bus6.getPower();
   
        Serial.print("Voltage: ");
        Serial.print(v, DEC);
        Serial.println(" mV");
 
        Serial.print("Current: ");
        Serial.print(i, DEC);
        Serial.println(" mA");
 
        Serial.print("Power ");
        Serial.print(p, DEC);
        Serial.println(" mW");
   
        // check that the values are within the correct range
        showResult((v > 3500) && (v < 5500) && (i > 0) && (i < 10) && (p > 10) && (p < 30));
    }
    else
    {
        Serial.println("INA226 not present");
        showResult(false);
    }
    
    // turn all the buses off
    switchOFF();
}

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


