#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32 
#define OLED_RESET     4 
#define SCREEN_ADDRESS 0x3C 
#define OK 38
#define LEFT 39
#define RIGHT 37
#define NB_MAX_CAPTEUR  3 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


struct bValue{
	int vleft;
	int vok;
	int vright;
};

struct bValue buttons;


int listCapteur[NB_MAX_CAPTEUR];
int actualMenu = 0;

void readbValue(struct bValue * b){
	b->vleft = digitalRead(LEFT);
	b->vok = digitalRead(OK);
	b->vright = digitalRead(RIGHT);
}

void printbValue(struct bValue * b){
	Serial.println(b->vleft);
	Serial.println(b->vok);
	Serial.println(b->vright);
}

void setupButton(){
  pinMode(OK,INPUT);
  pinMode(LEFT,INPUT);
  pinMode(RIGHT,INPUT);

}


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

//Menu principal du boitier.
int  mainMenu() {
  actualMenu = 1;
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println(F("Boitier de capteurs"));
  display.setCursor(0, 10);
  display.println(F("<= capteurs"));
  display.setCursor(65, 20);
  display.println(F("cadence =>")); 
  display.display();      
  delay(100);
  return 0;
}

//Menu catpeur du boitier.
int capteurMenu() {
  actualMenu = 2;
  //nbCapt=scanCapteur();
  int nbCapt=1;
  char charCapt = nbCapt;
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println(F(" Capteurs disponible")); 
  display.setTextSize(2); 
  display.setCursor(50, 10);
  //display.println(F(charCapt)); 
  display.display();
  delay(100);
  return 0;
}

//Menu actualisation pour regeler la frequence de recuperation des données. 
int actualisationMenu() {
  actualMenu = 2;    
  delay(100);
  return 0;
}
///////////////////////////////////////////////////////////
void setup() {
  Serial.begin(9600);
  if(!setOled())
	Serial.println("Oled failed to connect");
  delay(2000); 
  display.clearDisplay();
  mainMenu();
  delay(1000);
  capteurMenu();
  delay(1000);
  int nbc = scanCapteur(); 
  Serial.println(nbc);
}

void loop() {
  delay(10000);
  int nbc = scanCapteur(); 
  Serial.println(nbc);

}
