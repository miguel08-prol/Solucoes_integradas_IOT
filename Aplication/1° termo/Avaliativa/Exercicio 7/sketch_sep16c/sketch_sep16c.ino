const int lm35Pin = A0;
const int ledPin = 13;

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int sensorValue = analogRead(lm35Pin);

  float voltage = (sensorValue / 1024.0) * 5.0;

  float temperatureC = voltage * 100.0;

  if (temperatureC > 25.0) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

  delay(1000);
}
