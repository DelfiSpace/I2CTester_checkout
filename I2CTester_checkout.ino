#include <Wire.h>
#include "HelperFunctions.h"
#include "tests.h"

#define TEST_BUS_1        true
#define TEST_BUS_4        true
#define TEST_BUS_6        true

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
  
  delay(2000);
}
