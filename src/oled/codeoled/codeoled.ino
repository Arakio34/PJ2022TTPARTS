#include <SPI.h>
#include <Wire.h>
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "ttoled.h"
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);
  if(!setOled(&display))
	Serial.println("Oled failed to connect");
  display.clearDisplay();
  creditMenu(&display);
  delay(2000);
  mainMenu(&display);
}

void loop() {
	changeMenu(0,&display);	
	delay(3000);
	changeMenu(1,&display);	
	delay(3000);
	changeMenu(2,&display);	
	delay(3000);
}
