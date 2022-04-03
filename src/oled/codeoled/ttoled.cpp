#include <Arduino.h>
#include "ttoled.h"


//Scan les capteur brancher et retourne leur nombre 
int listCapteur[NB_MAX_CAPTEUR];
int actualMenu = 0;

int scanCapteur(){
	Wire.begin();
	byte addresse, erreur;
	int nbCapteur = 0;
	for(addresse = 0x01; addresse< 0x7f ; addresse++){
		Wire.beginTransmission(addresse);
		erreur = Wire.endTransmission();
		if(erreur == 0){
			nbCapteur++;
			listCapteur[nbCapteur]=addresse;
		}	
	}
	return nbCapteur;	
}

// Mets en fonctionnement le oled
int setOled(Adafruit_SSD1306 * display){
if(!display->begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    return -1;
  }
  display->setTextSize(1); 
  display->setTextColor(SSD1306_WHITE);
  display->println(F("Bonjour"));
  display->display();
  return 0;
}

int creditMenu(Adafruit_SSD1306 * display){
  display->clearDisplay();
  display->setCursor(0, 0);
  display->println(F("Project done by :"));
  display->setCursor(0, 10);
  display->println(F("T.T A.M T.C"));
  display->setCursor(10, 20);
  display->println(F("2021/2022")); 
  display->display();      
  delay(100);
  return 0;
}
//Menu principal du boitier.
int mainMenu(Adafruit_SSD1306 * display){
  actualMenu = 1;
  display->clearDisplay();
  display->setCursor(0, 0);
  display->println(F("Boitier modulaire"));
  display->setCursor(0, 10);
  display->println(F("<= capteurs"));
  display->setCursor(65, 20);
  display->println(F("cadence =>")); 
  display->display();      
  delay(100);
  return 0;
}

//Menu catpeur du boitier.
int sensorMenu(Adafruit_SSD1306 * display) {
  actualMenu = 0;
  display->clearDisplay();
  display->setCursor(0, 0);
  display->println(F(" Capteurs disponible")); 
  display->setCursor(0, 10);
  display->println(F("<= cadence"));
  display->setCursor(20, 20);
  display->println(F("menu principal =>")); 
  display->display();
  delay(100);
  return 0;
}

//Menu actualisation pour regeler la frequence de recuperation des données. 
int rateMenu(Adafruit_SSD1306 * display) {
  actualMenu = 2;    
  display->clearDisplay();
  display->setCursor(0, 0);
  display->println(F("Cadence")); 
  display->setCursor(0, 10);
  display->println(F("<= menu principal"));
  display->setCursor(60, 20);
  display->println(F("capteurs =>")); 
  display->display();
  delay(100);
  return 0;
}

void changeMenu(int id, Adafruit_SSD1306 * display){
	delay(300);
	switch (id){
		case 0:
			sensorMenu(display);
			break;
		case 1:
			mainMenu(display);
			break;
		case 2:
			rateMenu(display);
			break;
		default:
			break;
	}

}
