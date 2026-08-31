// Inclui a biblioteca do sensor DHT
#include "DHT.h"

// Configurações do Sensor DHT
#define DHTPIN 2       // Pino onde o sensor está conectado
#define DHTTYPE DHT11  // Define o tipo de sensor (DHT11)
DHT dht(DHTPIN, DHTTYPE);

// Pinos dos LEDs (3 LEDs - Semáforo)
const int led1Pin = 7;   // LED Verde
const int led2Pin = 8;   // LED Amarelo  
const int led3Pin = 9;   // LED Vermelho

void setup() {
  // Inicia a comunicação serial para o Python
  Serial.begin(9600);

  // Inicia o sensor DHT
  dht.begin();

  // Configura os pinos dos LEDs como saída
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(led3Pin, OUTPUT);

  // Iniciar com LEDs desligados
  digitalWrite(led1Pin, LOW);
  digitalWrite(led2Pin, LOW);
  digitalWrite(led3Pin, LOW);
  
  // Aguarda estabilização
  delay(2000);
  
  Serial.println("SISTEMA_INICIADO");
  Serial.println("COMANDOS: A,a,B,b,C,c,T,S,R");
}

void loop() {
  // Verifica se há algum comando vindo do Python
  if (Serial.available() > 0) {
    char command = Serial.read();
    
    // Processa o comando imediatamente
    processarComando(command);
  }
}

void processarComando(char command) {
  switch (command) {
    // Controle dos LEDs - VERDE
    case 'A':
      digitalWrite(led1Pin, HIGH);
      digitalWrite(led2Pin, LOW);
      digitalWrite(led3Pin, LOW);
      Serial.println("LED_VERDE_ON");
      break;
      
    case 'a':
      digitalWrite(led1Pin, LOW);
      Serial.println("LED_VERDE_OFF");
      break;
      
    // Controle dos LEDs - AMARELO  
    case 'B':
      digitalWrite(led1Pin, LOW);
      digitalWrite(led2Pin, HIGH);
      digitalWrite(led3Pin, LOW);
      Serial.println("LED_AMARELO_ON");
      break;
      
    case 'b':
      digitalWrite(led2Pin, LOW);
      Serial.println("LED_AMARELO_OFF");
      break;
      
    // Controle dos LEDs - VERMELHO
    case 'C':
      digitalWrite(led1Pin, LOW);
      digitalWrite(led2Pin, LOW);
      digitalWrite(led3Pin, HIGH);
      Serial.println("LED_VERMELHO_ON");
      break;
      
    case 'c':
      digitalWrite(led3Pin, LOW);
      Serial.println("LED_VERMELHO_OFF");
      break;
      
    // Comando para ler temperatura e umidade
    case 'T':
      lerSensorDHT();
      break;
      
    // Status dos LEDs
    case 'S':
      enviarStatusLEDs();
      break;
      
    // Reset todos LEDs
    case 'R':
      digitalWrite(led1Pin, LOW);
      digitalWrite(led2Pin, LOW);
      digitalWrite(led3Pin, LOW);
      Serial.println("LEDS_RESETADOS");
      break;
      
    default:
      Serial.println("COMANDO_INVALIDO");
      break;
  }
}

void lerSensorDHT() {
  // Lê a temperatura e umidade
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  // Verifica se a leitura falhou
  if (isnan(t) || isnan(h)) {
    Serial.println("ERRO_SENSOR");
  } else {
    // Envia os dados de volta para o Python no formato "TEMP;UMID"
    Serial.print("DADOS:");
    Serial.print(t, 1);  // 1 casa decimal
    Serial.print(";");
    Serial.println(h, 1); // 1 casa decimal
  }
}

void enviarStatusLEDs() {
  // Envia o status atual dos LEDs
  Serial.print("STATUS:");
  Serial.print(digitalRead(led1Pin) ? "VERDE_ON," : "VERDE_OFF,");
  Serial.print(digitalRead(led2Pin) ? "AMARELO_ON," : "AMARELO_OFF,");
  Serial.println(digitalRead(led3Pin) ? "VERMELHO_ON" : "VERMELHO_OFF");
}