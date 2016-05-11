#include <Wire.h>
#include <INA226.h>
#include <MAX1237.h>

#define BUS1       24
#define BUS2        5
#define BUS3       25
#define BUS4        6
#define BUS5       26
#define BUS6       27

unsigned char voltage[2];

INA226 one(0x40);
MAX1237 two;

unsigned char scanBus()
{
    unsigned char devices = 0;
    Serial.print("Scanning bus... ");
    for(unsigned char address = 1; address < 127; address++ )
    {
        Wire.beginTransmission(address);
        unsigned char count = Wire.requestFrom(address, (unsigned char)1);    // request 1 byte
        Wire.endTransmission();
        
        if (count != 0) 
        {
            devices++'
            Serial.print("Found Address 0x");
            if (address < 15) 
            {
                Serial.print('0');
            }
            Serial.println(address,HEX);
        }
    }   
    Serial.println("Scan completed");
    
    return devices;
}


void initGPIOs()
{
    // set-up power bus control pins
    
    // first set the pin low to avoid glitches
    digitalWrite(BUS1, LOW);
    digitalWrite(BUS2, LOW);
    digitalWrite(BUS3, LOW);
    digitalWrite(BUS4, LOW);
    digitalWrite(BUS5, LOW);
    digitalWrite(BUS6, LOW);
    
    // then set the pin directio to output
    pinMode(BUS1, OUTPUT);
    pinMode(BUS2, OUTPUT);
    pinMode(BUS3, OUTPUT);
    pinMode(BUS4, OUTPUT);
    pinMode(BUS5, OUTPUT);
    pinMode(BUS6, OUTPUT);
}

void setup()
{
  // Initialize I2C master
  // TODO: speed?????
  Wire.begin();
  
  // initialize debug UART
  Serial.begin(9600);

  // wait to make sure the UART is initialized
  delay(200);
  
  // initialize the GPIOs used to control the power buses
  initGPIOs();
  
  scanBus();
  delay(1000);
  
  digitalWrite(BUS6, HIGH);
  scanBus();
  
  digitalWrite(BUS6, LOW);
  
  //Serial.print("INA226 present ");
  //Serial.println(one.ping(), DEC);
  
  //one.setShuntResistor(0.05);
  
  //two.writeRegister(0x80 | 0x02 | (0x05 << 4));
  //two.writeRegister(CS2 | SCAN3 | 1);
  
  
}

void loop()
{
  /*
   unsigned short v = one.getVoltage();
   signed short i = one.getCurrent();
   unsigned short p = one.getPower();
   
   Serial.print("Voltage: ");
   Serial.print(v, DEC);
   Serial.println(" mV");
 
   Serial.print("Current: ");
   Serial.print(i, DEC);
   Serial.println(" mA");
 
   Serial.print("Power ");
   Serial.print(p, DEC);
   Serial.println(" mW");
   
   Serial.println();
   */
   //Serial.print("ADC ");
   //Serial.print(two.readSingleChannel() >> 1, DEC);
   //Serial.println(" mV");
   
   //Serial.println();
   
   
   delay(1500);
   digitalWrite(BUS6, LOW);
   digitalWrite(BUS1, HIGH);
   delay(1500);
   digitalWrite(BUS1, LOW);
   digitalWrite(BUS2, HIGH);
   delay(1500);
   digitalWrite(BUS2, LOW);
   digitalWrite(BUS3, HIGH);
   delay(1500);
   digitalWrite(BUS3, LOW);
   digitalWrite(BUS4, HIGH);
   delay(1500);
   digitalWrite(BUS4, LOW);
   digitalWrite(BUS5, HIGH);
   delay(1500);
   digitalWrite(BUS5, LOW);
   digitalWrite(BUS6, HIGH);
   //digitalWrite(27, HIGH);
   //delay(500);
   //digitalWrite(27, LOW);
}
