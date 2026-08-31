// Sistema Residencial Inteligente - Monitoramento de Temperatura
#include "DHT.h"

// Configurações do Sensor DHT
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Pinos dos LEDs para alertas
const int ledNormalPin = 7;      // LED Verde - Temperatura normal
const int ledAlertaPin = 8;      // LED Vermelho - Alerta temperatura
const int ledGeladeiraPin = 9;   // LED Amarelo - Alerta geladeira

// Pinos para controle de dispositivos (simulados com LEDs)
const int ventiladorPin = 10;    // Simula ventilador
const int aquecedorPin = 11;     // Simula aquecedor

// Limites de temperatura
const float TEMP_ALTA_LIMITE = 28.0;   // Acima disso: muito quente
const float TEMP_BAIXA_LIMITE = 18.0;  // Abaixo disso: muito frio
const float GELADEIRA_ALTA = 8.0;      // Alerta geladeira acima disso
const float GELADEIRA_BAIXA = -5.0;    // Alerta freezer abaixo disso

// Variáveis de estado
bool alertaTemperatura = false;
bool alertaGeladeira = false;
bool ventiladorLigado = false;
bool aquecedorLigado = false;
unsigned long ultimoAlerta = 0;
const unsigned long INTERVALO_ALERTA = 1000; // 1 segundo para piscar

void setup() {
  Serial.begin(9600);
  dht.begin();

  // Configura os pinos como saída
  pinMode(ledNormalPin, OUTPUT);
  pinMode(ledAlertaPin, OUTPUT);
  pinMode(ledGeladeiraPin, OUTPUT);
  pinMode(ventiladorPin, OUTPUT);
  pinMode(aquecedorPin, OUTPUT);

  // Iniciar com tudo desligado
  digitalWrite(ledNormalPin, LOW);
  digitalWrite(ledAlertaPin, LOW);
  digitalWrite(ledGeladeiraPin, LOW);
  digitalWrite(ventiladorPin, LOW);
  digitalWrite(aquecedorPin, LOW);
  
  delay(2000);
  
  Serial.println("SISTEMA_RESIDENCIAL_INICIADO");
  Serial.println("COMANDOS: T,S,R,V,v,A,a");
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();
    processarComando(command);
  }
  
  gerenciarAlertas();
}

void processarComando(char command) {
  switch (command) {
    case 'T': // Ler sensor
      lerSensorDHT();
      break;
      
    case 'S': // Status
      enviarStatusSistema();
      break;
      
    case 'R': // Reset
      resetarSistema();
      break;
      
    case 'V': // Ventilador ON
      ligarVentilador();
      break;
      
    case 'v': // Ventilador OFF
      desligarVentilador();
      break;
      
    case 'A': // Aquecedor ON
      ligarAquecedor();
      break;
      
    case 'a': // Aquecedor OFF
      desligarAquecedor();
      break;
      
    default:
      Serial.println("COMANDO_INVALIDO");
      break;
  }
}

void lerSensorDHT() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  if (isnan(t) || isnan(h)) {
    Serial.println("ERRO_SENSOR");
    return;
  }
  
  processarAlertasTemperatura(t);
  
  Serial.print("DADOS:");
  Serial.print(t, 1);
  Serial.print(";");
  Serial.print(h, 1);
  Serial.print(";");
  Serial.print(alertaTemperatura ? "ALERTA_TEMP," : "NORMAL_TEMP,");
  Serial.print(alertaGeladeira ? "ALERTA_GELADEIRA," : "NORMAL_GELADEIRA,");
  Serial.print(ventiladorLigado ? "VENTILADOR_ON," : "VENTILADOR_OFF,");
  Serial.println(aquecedorLigado ? "AQUECEDOR_ON" : "AQUECEDOR_OFF");
}

void processarAlertasTemperatura(float temperatura) {
  bool alertaAnteriorTemp = alertaTemperatura;
  bool alertaAnteriorGel = alertaGeladeira;
  
  alertaTemperatura = (temperatura > TEMP_ALTA_LIMITE || temperatura < TEMP_BAIXA_LIMITE);
  alertaGeladeira = (temperatura > GELADEIRA_ALTA || temperatura < GELADEIRA_BAIXA);
  
  atualizarLEDs();
  
  if (alertaTemperatura != alertaAnteriorTemp) {
    if (alertaTemperatura) {
      Serial.println("ALERTA: Temperatura fora dos limites normais!");
    }
  }
  
  if (alertaGeladeira != alertaAnteriorGel) {
    if (alertaGeladeira) {
      Serial.println("ALERTA_CRITICO: Problema na geladeira/freezer!");
    }
  }
  
  // Controle automático (opcional)
  if (temperatura > TEMP_ALTA_LIMITE && !ventiladorLigado) {
    Serial.println("SUGESTÃO: Ligar ventilador");
  }
  if (temperatura < TEMP_BAIXA_LIMITE && !aquecedorLigado) {
    Serial.println("SUGESTÃO: Ligar aquecedor");
  }
}

void atualizarLEDs() {
  if (alertaGeladeira) {
    digitalWrite(ledGeladeiraPin, HIGH);
    digitalWrite(ledAlertaPin, LOW);
    digitalWrite(ledNormalPin, LOW);
  } else if (alertaTemperatura) {
    digitalWrite(ledAlertaPin, HIGH);
    digitalWrite(ledGeladeiraPin, LOW);
    digitalWrite(ledNormalPin, LOW);
  } else {
    digitalWrite(ledNormalPin, HIGH);
    digitalWrite(ledAlertaPin, LOW);
    digitalWrite(ledGeladeiraPin, LOW);
  }
}

void gerenciarAlertas() {
  unsigned long tempoAtual = millis();
  
  if (alertaGeladeira && (tempoAtual - ultimoAlerta >= INTERVALO_ALERTA)) {
    digitalWrite(ledGeladeiraPin, !digitalRead(ledGeladeiraPin));
    ultimoAlerta = tempoAtual;
  }
}

void enviarStatusSistema() {
  Serial.print("STATUS:");
  Serial.print(digitalRead(ledNormalPin) ? "NORMAL_ON," : "NORMAL_OFF,");
  Serial.print(digitalRead(ledAlertaPin) ? "ALERTA_ON," : "ALERTA_OFF,");
  Serial.print(digitalRead(ledGeladeiraPin) ? "GELADEIRA_ON," : "GELADEIRA_OFF,");
  Serial.print(ventiladorLigado ? "VENTILADOR_ON," : "VENTILADOR_OFF,");
  Serial.println(aquecedorLigado ? "AQUECEDOR_ON" : "AQUECEDOR_OFF");
}

void resetarSistema() {
  alertaTemperatura = false;
  alertaGeladeira = false;
  desligarVentilador();
  desligarAquecedor();
  atualizarLEDs();
  Serial.println("SISTEMA_RESETADO");
}

void ligarVentilador() {
  ventiladorLigado = true;
  digitalWrite(ventiladorPin, HIGH);
  Serial.println("VENTILADOR_LIGADO");
}

void desligarVentilador() {
  ventiladorLigado = false;
  digitalWrite(ventiladorPin, LOW);
  Serial.println("VENTILADOR_DESLIGADO");
}

void ligarAquecedor() {
  aquecedorLigado = true;
  digitalWrite(aquecedorPin, HIGH);
  Serial.println("AQUECEDOR_LIGADO");
}

void desligarAquecedor() {
  aquecedorLigado = false;
  digitalWrite(aquecedorPin, LOW);
  Serial.println("AQUECEDOR_DESLIGADO");
}