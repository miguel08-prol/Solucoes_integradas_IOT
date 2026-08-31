const int verdeCarro = 10;
const int amareloCarro = 9;
const int vermelhoCarro = 8;
const int ledPedestre = 11;

const int botao = 2;
int estadoBotao = 0;

void setup() {
  pinMode(verdeCarro, OUTPUT);
  pinMode(amareloCarro, OUTPUT);
  pinMode(vermelhoCarro, OUTPUT);
  pinMode(ledPedestre, OUTPUT);
  pinMode(botao, INPUT); 

  Serial.begin(9600);
  Serial.println("Semaforo Ativo");

  cicloNormal();
}

void loop() {
  estadoBotao = digitalRead(botao);

  if (estadoBotao == HIGH) {
    cicloPedestre();
    delay(500); 
  }
}

void cicloNormal() {
  digitalWrite(verdeCarro, HIGH);
  digitalWrite(amareloCarro, LOW);
  digitalWrite(vermelhoCarro, LOW);
  digitalWrite(ledPedestre, LOW);
  Serial.println("Semaforo para carros: VERDE");
}

void cicloPedestre() {
  Serial.println("Botao acionado. Iniciando ciclo para pedestre.");

  digitalWrite(verdeCarro, LOW);
  digitalWrite(amareloCarro, HIGH); 
  Serial.println("Semaforo para carros: AMARELO");
  delay(2000);

  digitalWrite(amareloCarro, LOW);
  digitalWrite(vermelhoCarro, HIGH); 
  digitalWrite(ledPedestre, HIGH); 
  Serial.println("Semaforo para carros: VERMELHO. Semaforo para pedestre: BRANCO");
  delay(5000);

  digitalWrite(ledPedestre, LOW);
  
  digitalWrite(vermelhoCarro, LOW);
  Serial.println("Semaforo para pedestre: desligado. Voltando ao ciclo normal.");
  cicloNormal();
}