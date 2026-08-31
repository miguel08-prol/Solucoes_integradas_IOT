#include <DHT.h> 

const int pinoDHT = 7;      
#define DHTTYPE DHT11       

DHT dht(pinoDHT, DHTTYPE);  

const int ledVerde = 2;     
const int ledAmarelo = 3;   
const int ledVermelho = 4;  

const float tempNormal = 25.0;      
const float tempQuente = 30.0;    

void setup() {
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("Iniciando sensor DHT...");
  dht.begin(); 
}

void loop() {
  delay(2000);

  float umidade = dht.readHumidity();
  float temperatura = dht.readTemperature();

  if (isnan(umidade) || isnan(temperatura)) {
    Serial.println("Falha na leitura do sensor DHT!");
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVermelho, LOW);
    return;
  }
  Serial.print("Umidade: ");
  Serial.print(umidade);
  Serial.print(" %\t");
  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println(" °C");

  if (temperatura < tempNormal) {
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVermelho, LOW);
  } else if (temperatura >= tempNormal && temperatura < tempQuente) {
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, HIGH);
    digitalWrite(ledVermelho, LOW);
  } else {
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVermelho, HIGH);
  }
}