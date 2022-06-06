#include "EspMQTTClient.h"
#include "Adafruit_Si7021.h"

bool enableHeater = false;
uint8_t loopCnt = 0;

Adafruit_Si7021 sensor = Adafruit_Si7021();

EspMQTTClient client(
  "Livebox-FC40",
  "jJ5nqDP5VGDzJ6bheQ",
  "194.199.227.239",  // MQTT Ip
  "",   
  "",   
  "ESP32-Tom",     // Client name 
  1883              // MQTT port
);
  
int setupSi7021(){
  if (!sensor.begin()) {
    Serial.println("Did not find Si7021 sensor!");
    while (true)
      return -1;;
  }
  return 0; 
}

void setup()
{
 
  Serial.begin(115000);
  client.enableLastWillMessage("TestClient/lastwill", "I am going offline");
  onConnectionEstablished();
}

// This function is called once everything is connected (Wifi and MQTT)
void onConnectionEstablished()
{
  client.publish("test", "This is a message"); 
}

void loop()
{
  int humidity = sensor.readHumidity();
  int temperature = sensor.readTemperature();
  client.publish("mesures/temp", (String)temperature); 
  client.publish("mesures/humi", (String)humidity); 
  
  delay(1000);
  client.loop();
  
  if (++loopCnt == 30) {
    enableHeater = !enableHeater;
    sensor.heater(enableHeater);
    Serial.print("Heater Enabled State: ");
    if (sensor.isHeaterEnabled())
      Serial.println("ENABLED");
    else
      Serial.println("DISABLED");
       
    loopCnt = 0;
 
    }
}
