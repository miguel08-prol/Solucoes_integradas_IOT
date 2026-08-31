void setup() {
 pinMode(2, OUTPUT);
 pinMode(3, OUTPUT);
 pinMode(4, OUTPUT);
 pinMode(5, OUTPUT);
}

void loop() {
  digitalWrite(2, HIGH);
  delay(30);
  digitalWrite(3, HIGH);
  delay(40);
  digitalWrite(4, HIGH);
  delay(50);
  digitalWrite(5, HIGH);
  delay(100);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  delay(1000);
}
