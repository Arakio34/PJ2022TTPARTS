// CO2 Meter K-series Example Interface 
// Revised by Marv Kausch, 7/2016 at CO2 Meter <co2meter.com> 
// Talks via I2C to K30/K33 Sensors and displays CO2 values 
#include <Wire.h> 
// We will be using the I2C hardware interface on the Arduino in 
// combination with the built-in Wire library to interface. 
// Arduino analog input 5 - I2C SCL 
// Arduino analog input 4 - I2C SDA 

int co2Addr = 0x68; 
// This is the default address of the CO2 sensor, 7bits shifted left. 
void setup() { 
  Serial.begin(9600); 
  Wire.begin (); 
  Serial.println("Application Note AN-102: Interface Arduino to K-30"); 
} 

int readCO2() 
{ 
  int co2_value = 0;  // Store the CO2 value inside this variable. 
 

  Wire.beginTransmission(co2Addr); 
  Wire.write(0x22); 
  Wire.write(0x00); 
  
 
  Wire.write(0x08); 
  Wire.write(0x2A); 
 
  Wire.endTransmission(); 
 
  ///////////////////////// 
  /* End Write Sequence. */ 
  ///////////////////////// 
 
 
 
  delay(10); 
 
  ///////////////////////// 
  /* Begin Read Sequence */ 
  ///////////////////////// 
 

 
  Wire.requestFrom(co2Addr, 4); 
 
  byte i = 0; 
  byte buffer[4] = {0, 0, 0, 0}; 
 

 
  while (Wire.available()) 
  { 
    buffer[i] = Wire.read(); 
    i++; 
  } 
 
  /////////////////////// 
  /* End Read Sequence */ 
  /////////////////////// 
   
 
 
  co2_value = 0; 
  co2_value |= buffer[1] & 0xFF; 
  co2_value = co2_value << 8; 
  co2_value |= buffer[2] & 0xFF; 
 
  byte sum = 0; //Checksum Byte 
  sum = buffer[0] + buffer[1] + buffer[2]; //Byte addition utilizes overflow 
 
  if (sum == buffer[3]) 
  { 
    // Success! 
    Serial.println("Sucess");
    return co2_value; 
  } 
  else 
  { 

    Serial.println("Sucess");
 
    return 0; 
  } 
} 
void loop() { 
 
  int co2Value = readCO2(); 
  if (co2Value > 0) 
  { 
    Serial.print("CO2 Value: "); 
    Serial.println(co2Value); 
  } 
  else 
  { 
    Serial.println("Checksum failed / Communication failure"); 
  } 
  delay(2000); 
} 
 
