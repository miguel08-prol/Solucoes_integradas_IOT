const int LED[] = {2, 3, 4, 5, 6};
const int numLEDs = 10;

const int pinoPotenciometro = A0;

void setup() {
  for (int i = 0; i < numLEDs; i++) {
    pinMode(LED[i], OUTPUT);
  }
}

void loop() {
  int valorPotenciometro = analogRead(pinoPotenciometro);
  int ledsParaAcender = map(valorPotenciometro, 0, 1023, 0, numLEDs);
  
  for (int i = 0; i < numLEDs; i++) {
    if (i < ledsParaAcender) {
      digitalWrite(LED[i], HIGH); 
    } else {
      digitalWrite(LED[i], LOW);  
    }
  }
  
  delay(10); 
}
