#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32 
#define OLED_RESET     4 
#define SCREEN_ADDRESS 0x3C 
#define NB_MAX_CAPTEUR  3 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);



int listCapteur[NB_MAX_CAPTEUR];
int actualMenu = 0;

//Scan les capteur brancher et retourne leur nombre 
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
int setOled(){
if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    return -1;
  }
  display.setTextSize(1); 
  display.setTextColor(SSD1306_WHITE);
  display.display();
  return 0;
}

int  creditMenu() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println(F("Done by :"));
  display.setCursor(0, 10);
  display.println(F("T.T. A.M. T.C."));
  display.setCursor(10, 20);
  display.println(F("2021/2022")); 
  display.display();      
  delay(100);
  return 0;
}
//Menu principal du boitier.
int  mainMenu() {
  actualMenu = 1;
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println(F("Boitier modulaire"));
  display.setCursor(0, 10);
  display.println(F("<= capteurs"));
  display.setCursor(65, 20);
  display.println(F("cadence =>")); 
  display.display();      
  delay(100);
  return 0;
}

//Menu catpeur du boitier.
int sensorMenu() {
  actualMenu = 0;
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println(F(" Capteurs disponible")); 
  display.setCursor(0, 10);
  display.println(F("<= cadence"));
  display.setCursor(20, 20);
  display.println(F("menu principal =>")); 
  display.display();
  delay(100);
  return 0;
}

//Menu actualisation pour regeler la frequence de recuperation des données. 
int rateMenu() {
  actualMenu = 2;    
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println(F("Cadence")); 
  display.setCursor(0, 10);
  display.println(F("<= menu principal"));
  display.setCursor(60, 20);
  display.println(F("capteurs =>")); 
  display.display();
  delay(100);
  return 0;
}

void changeMenu(int id){
	delay(300);
	switch (id){
		case 0:
			sensorMenu();
			break;
		case 1:
			mainMenu();
			break;
		case 2:
			rateMenu();
			break;
		default:
			break;
	}

}
void setup() {
  Serial.begin(9600);
  if(!setOled())
	Serial.println("Oled failed to connect");
  display.clearDisplay();
  creditMenu();
  delay(2000);
  mainMenu();
}

void loop() {
	changeMenu(0);	
	delay(3000);
	changeMenu(1);	
	delay(3000);
	changeMenu(2);	
	delay(3000);
}
