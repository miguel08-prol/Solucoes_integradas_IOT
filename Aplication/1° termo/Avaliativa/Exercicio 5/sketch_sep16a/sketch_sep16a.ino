const int ledPin = 11;      
const int pirPin = 10;      

int pessoasContadas = 0;
int estadoAnteriorPir = LOW;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(pirPin, INPUT);

  Serial.begin(9600);
  Serial.println("Contador de Pessoas Ativo");
}

void loop() {
  int estadoAtualPir = digitalRead(pirPin);

  if (estadoAtualPir == HIGH && estadoAnteriorPir == LOW) {
    // Acende o LED
    digitalWrite(ledPin, HIGH);

    pessoasContadas++;

    Serial.print("Pessoa detectada! Total: ");
    Serial.println(pessoasContadas);

    delay(1000); 
  }

  if (estadoAtualPir == LOW) {
    digitalWrite(ledPin, LOW);
  }

  estadoAnteriorPir = estadoAtualPir;
}