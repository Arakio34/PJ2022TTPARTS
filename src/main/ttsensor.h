#ifndef TTSENSOR_H
#define TTSENSOR_H

#include "EspMQTTClient.h"
#include "Adafruit_Si7021.h"

int readCO2(); 

int setupSi7021();

int sendData(const char * topic, double data,EspMQTTClient * client);

int sendDataHT(const char * topicH, const char * topicT,EspMQTTClient * client);

void setupMqtt(EspMQTTClient * client);

void loopData(EspMQTTClient * client);

void onConnectionEstablished();
#endif
