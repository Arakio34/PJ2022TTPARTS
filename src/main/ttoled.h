#ifndef TTOLED_H
#define TTOLED_H


#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32 
#define OLED_RESET     4 
#define SCREEN_ADDRESS 0x3C 
#define NB_MAX_CAPTEUR  3 



//Scan les capteur brancher et retourne leur nombre 
int scanCapteur();

// Mets en fonctionnement le oled
int setOled(Adafruit_SSD1306 * display);

int  creditMenu(Adafruit_SSD1306 * display);

//Menu principal du boitier.
int  mainMenu(Adafruit_SSD1306 * display);

//Menu catpeur du boitier.
int sensorMenu(Adafruit_SSD1306 * display);

//Menu actualisation pour regeler la frequence de recuperation des données. 
int rateMenu(Adafruit_SSD1306 * display);

void changeMenu(int id, Adafruit_SSD1306 * display);

int fctActualMenu();

#endif
