const int trigPin = 7;
const int echoPin = 8;
const int buzzerPin = 13;

const long distanciaLimite = 20;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duracao = pulseIn(echoPin, HIGH);
  long distanciaCm = duracao * 0.034 / 2;

  Serial.print("Distancia: ");
  Serial.print(distanciaCm);
  Serial.println(" cm");

  if (distanciaCm < distanciaLimite && distanciaCm > 0) {
    digitalWrite(buzzerPin, HIGH);
  } else {
    digitalWrite(buzzerPin, LOW);
  }

  delay(100);
}