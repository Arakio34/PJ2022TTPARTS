#include <Arduino.h>
#include "ttbutton.h"

void setupButton(struct bValue * b, int tleft, int tok, int tright){
  b->ok=tok;
  b->left=tleft;
  b->right=tright;
  pinMode(tok,INPUT);
  pinMode(tleft,INPUT);
  pinMode(tright,INPUT);
}
void readbValue(struct bValue * b){
	b->vleft = digitalRead(b->left);
	b->vok = digitalRead(b->ok);
	b->vright = digitalRead(b->right);
}

void printbValue(struct bValue * b){
	Serial.println(b->vleft);
	Serial.println(b->vok);
	Serial.println(b->vright);
}


