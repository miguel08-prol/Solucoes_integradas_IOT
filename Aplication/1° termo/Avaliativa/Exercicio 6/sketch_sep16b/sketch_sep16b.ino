const int ldrPin = A0;
const int ledPin = 13;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int valorLuminosidade = analogRead(ldrPin);

  Serial.print("Valor da luminosidade: ");
  Serial.println(valorLuminosidade);

  if (valorLuminosidade < 300) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

  delay(500);
}