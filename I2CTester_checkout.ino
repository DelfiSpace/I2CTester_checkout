#include <Wire.h>
#include "HelperFunctions.h"
#include "tests.h"

void setup()
{
  // Initialize I2C master
  // TODO: speed?????
  Wire.begin();
  
  // initialize debug UART
  Serial.begin(9600);

  // wait to make sure the UART is initialized
  delay(10);
  
  // initialize the GPIOs used to control the power buses
  initTests();
}

void loop()
{
  Serial.println();
  Serial.println("-----------------------------------------------------");
  Serial.println("---------    I2CTester Checkout Software    ---------");
  Serial.println("-----------------------------------------------------");
  Serial.println();
  
  // run all the tests in sequence
  // All busses off, list if any device is on
  Test1();
  
  // check if there are 2 devices on bus 1
  Test2();
  
  // check if the INA226 on bus 1 works 
  Test3();
  
  // check if the MAX1237 on bus 1 works 
  Test4();
  
  // check if there are 2 devices on bus 6
  Test5();

  // check if the INA226 on bus 6 works 
  Test6();
  
  delay(2000);
}
