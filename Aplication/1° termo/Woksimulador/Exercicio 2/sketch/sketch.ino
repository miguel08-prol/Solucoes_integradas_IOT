void setup() {
  pinMode(13, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(4, OUTPUT);
}

void loop() {
digitalWrite(13, HIGH);
delay(1000);
digitalWrite(13, LOW);
delay(1000);
digitalWrite(7, HIGH);
delay(2000);
digitalWrite(7, LOW);
delay(2000);
digitalWrite(4, HIGH);
delay(3000);
digitalWrite(4, LOW);
delay(3000);
}
