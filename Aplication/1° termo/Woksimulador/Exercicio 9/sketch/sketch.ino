
const int pinoVermelho = 9;
const int pinoVerde = 10;
const int pinoAzul = 11;

void setup() {
}

void loop() {
  misturarCores(255, 0, 255);
  delay(1000);
  
  misturarCores(0, 255, 255);
  delay(1000);

  misturarCores(255, 255, 0);
  delay(1000);
  
  misturarCores(255, 255, 255);
  delay(1000);
  
  misturarCores(255, 0, 0);
  delay(1000);
  
  misturarCores(0, 255, 0);
  delay(1000);
  
  misturarCores(0, 0, 255);
  delay(1000);
}

void misturarCores(int vermelho, int verde, int azul) {
  analogWrite(pinoVermelho, vermelho);
  analogWrite(pinoVerde, verde);
  analogWrite(pinoAzul, azul);
}