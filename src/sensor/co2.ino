#include <Wire.h> 

int co2Addr = 0x68; 

void setup() { 
  Serial.begin(9600); 
  Wire.begin (); 
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
 
 
  delay(10); 
 
  Wire.requestFrom(co2Addr, 4); 
 
  byte i = 0; 
  byte buffer[4] = {0, 0, 0, 0}; 
 
  while (Wire.available()) 
  { 
    buffer[i] = Wire.read(); 
    i++; 
  } 
 
  co2_value = 0; 
  co2_value |= buffer[1] & 0xFF; 
  co2_value = co2_value << 8; 
  co2_value |= buffer[2] & 0xFF; 
 
  byte sum = 0; //Checksum Byte 
  sum = buffer[0] + buffer[1] + buffer[2]; //Byte addition utilizes overflow 
 
  if (sum == buffer[3]) 
  { 
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
 
