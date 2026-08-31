int led = 4;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(A0, INPUT);
}

void loop() {
  int leitura = analogRead(A0); 
  int pwm = map(leitura,0,1023,0,255);
  analogWrite(led, pwm);
}