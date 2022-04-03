#include "EspMQTTClient.h"

EspMQTTClient client(
  "Livebox-FC40",
  "jJ5nqDP5VGDzJ6bheQ",
  "194.199.227.239",  // MQTT Broker server ip
  "",   // Can be omitted if not needed
  "",   // Can be omitted if not needed
  "ESP32-Tom",     // Client name that uniquely identify your device
  1883              // The MQTT port, default to 1883. this line can be omitted
);
  


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
  client.publish("test", "ESP32"); 
  delay(1000);
  client.loop();
 
   
}
