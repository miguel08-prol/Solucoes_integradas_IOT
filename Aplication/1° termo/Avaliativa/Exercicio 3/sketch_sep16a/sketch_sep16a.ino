#include <Servo.h>

Servo meuServo;
const int pinoPotenciometro = A0;
const int pinoServo = 9;

void setup() {
  meuServo.attach(pinoServo);
  Serial.begin(9600);
}

void loop() {
  int valorPotenciometro = analogRead(pinoPotenciometro);
  int anguloServo = map(valorPotenciometro, 0, 1023, 0, 180);
  meuServo.write(anguloServo);
  Serial.print("Valor do Potenciometro: ");
  Serial.print(valorPotenciometro);
  Serial.print(" -> Angulo do Servo: ");
  Serial.print(anguloServo);
  Serial.println(" graus");
  delay(15);
}
