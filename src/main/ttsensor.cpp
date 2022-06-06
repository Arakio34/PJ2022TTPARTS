#include <Arduino.h>
#include "ttsensor.h"

Adafruit_Si7021 sensor = Adafruit_Si7021();

int setupSi7021(){
  if (!sensor.begin()) {
    Serial.println("Did not find Si7021 sensor!");
    while (true)
      return -1;;
  }
  Serial.println("Sucess Si7021");
  return 0; 
}


void setupMqtt(EspMQTTClient * client)
{ 
  client->enableLastWillMessage("TestClient/lastwill", "I am going offline");
  Serial.println("Sucess mqtt");
}


int sendData(const char * topic, double data,EspMQTTClient * client)
{
  client->publish(topic, (String)data); 
}	

int sendDataHT(const char * topicH, const char * topicT,EspMQTTClient * client)
{
  double humidity = sensor.readHumidity();
  double temperature = sensor.readTemperature();
  if(client->publish(topicT, (String)temperature)!=0)
  {
	  Serial.println("jpp");
  } 

  client->publish(topicH, (String)humidity); 
} 

void onConnectionEstablished()
{
}

void loopData(EspMQTTClient * client)
{
for(;;)
{
	sendDataHT("humi","temp",client);
	sendData("co2",readCO2(),client);
	delay(2000);
	client->loop();
}
}

int readCO2() 
{ 
  int co2Addr = 0x68; 
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
    Serial.println(co2_value);
    Serial.println("Sucess Co2");
    return co2_value; 
  } 
  else 
  { 

    Serial.println("Sucess");
 
    return 0; 
  } 
} 
