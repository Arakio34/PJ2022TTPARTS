#include <SPI.h>
#include <Wire.h>
#include <WiFi.h>
#include <MQTTPubSubClient.h>
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "ttoled.h"
#include "ttsensor.h"
#include "ttbutton.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
const char* ssid = "tominator";
const char* pass = "TOMVALERIEERIC0";

WiFiClient client;
MQTTPubSubClient mqtt;

int state = 0;
struct bValue buttons;

void setup() 
{
  Serial.begin(9600);
///////////////////////////////////////////////////////////////////////////

    WiFi.begin(ssid, pass);

    Serial.print("connecting to wifi...");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(1000);
    }
    Serial.println(" connected!");

    Serial.print("connecting to host...");
    while (!client.connect("194.199.227.239", 1883)) {
        Serial.print(".");
        delay(1000);
    }
    mqtt.begin(client);
    Serial.print("connecting to mqtt broker...");
    while (!mqtt.connect("arduino", "public", "public")) {
        Serial.print(".");
        delay(1000);
    }
/////////////////////////////////////////////////////////////////////////////
  if(!setOled(&display))
	Serial.println("Oled failed to connect");
  display.clearDisplay();
  creditMenu(&display);
  delay(2000);
  mainMenu(&display);
  setupButton(&buttons,19,18,5);
}

void loop() 
{
int change = 0;
if(state == 0)
{
	readbValue(&buttons);
	int actualMenu=fctActualMenu();
	if(change == 0 && buttons.vleft == 1)
	{
		if(actualMenu-1 < 0)
		{
			changeMenu(2,&display);	
			change = 1;
		}
		else
		{
			changeMenu(actualMenu-1,&display);
			change = 1;
		}
	}	
	if(change == 0 && buttons.vright == 1)
	{
		if(actualMenu+1 > 2)
		{
			changeMenu(0,&display);	
			change = 1;
		}
		else
		{
			changeMenu(actualMenu+1,&display);
			change = 1;
		}
	}	
	if(buttons.vok == 1)
	{
		if(actualMenu == 0)
		{
			loopData(&mqtt);
		}
	}	
}
}
