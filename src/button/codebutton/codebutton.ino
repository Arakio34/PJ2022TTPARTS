#include "ttbutton.h"
struct bValue buttons;

void setup() {
  Serial.begin(9600);
  setupButton(&buttons,19,18,5);
  Serial.println("Debut test");
}

void loop() {
  readbValue(&buttons); 
  printbValue(&buttons); 
  delay(1000);
}
