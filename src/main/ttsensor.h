#ifndef TTSENSOR_H
#define TTSENSOR_H

#include "MQTTPubSubClient.h"
#include "WiFi.h"
#include "Adafruit_Si7021.h"

int readCO2(); 

int setupSi7021();

int sendData(const char * topic, double data,MQTTPubSubClient * client);

int sendDataHT(const char * topicH, const char * topicT,MQTTPubSubClient * client);

void loopData(MQTTPubSubClient * client);

void onConnectionEstablished();
#endif
