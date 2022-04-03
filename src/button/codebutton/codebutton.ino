int ok = 38;
int left = 39;
int right = 37;
struct bValue{
	int vleft;
	int vok;
	int vright;
};

struct bValue buttons;

void readbValue(struct bValue * b){
	b->vleft = digitalRead(left);
	b->vok = digitalRead(ok);
	b->vright = digitalRead(right);
}

void printbValue(struct bValue * b){
	Serial.println(b->vleft);
	Serial.println(b->vok);
	Serial.println(b->vright);
}
void setup() {
  Serial.begin(9600);
  pinMode(ok,INPUT);
  pinMode(left,INPUT);
  pinMode(right,INPUT);
  Serial.println("Debut test");
}

void loop() {
  readbValue(&buttons); 
  printbValue(&buttons); 
  delay(1000);
}
