int led = 3;
void setup() {
  pinMode(led, OUTPUT);
  digitalWrite(led,HIGH);
}

void loop() {
    delay(300);
    digitalWrite(led,HIGH);
    delay(300);
    digitalWrite(led,LOW);

}
