const int ledvermelho = 12;
const int botao = 8;

int botao2 = 0;

void setup() {
  pinMode(ledvermelho, OUTPUT);
  pinMode(botao, INPUT);
}

void loop() {
  botao2 = digitalRead(botao);
  if (botao2 == HIGH) {
    digitalWrite(ledvermelho, HIGH);
  } else {
    digitalWrite(ledvermelho, LOW);
  }
}