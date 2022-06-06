#include <SPI.h>
#include <Wire.h>
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "ttoled.h"
#include "ttsensor.h"
#include "ttbutton.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

EspMQTTClient client(
  "tominator",
  "TOMVALERIEERIC0",
  "192.168.1.57",  // MQTT Ip
  "",   
  "",   
  "ESP32-Tom",     // Client name 
  1883              // MQTT port
);

int state = 0;
struct bValue buttons;

void setup() 
{
  Serial.begin(9600);
  if(!setOled(&display))
	Serial.println("Oled failed to connect");
  display.clearDisplay();
  creditMenu(&display);
  delay(2000);
  setupMqtt(&client);
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
			loopData(&client);
		}
	}	
}
}
