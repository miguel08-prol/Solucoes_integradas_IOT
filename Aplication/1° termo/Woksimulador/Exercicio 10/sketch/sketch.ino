const int ledPin = 13; 
const int dotDuration = 200; 

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
 String message = "SOS"; 
  
  for (int i = 0; i < message.length(); i++) {
    char c = tolower(message.charAt(i)); 
    if (c == ' ') {
      delay(dotDuration * 7); 
    } else {
      String morse = morseCodeMap(c);
      for (int j = 0; j < morse.length(); j++) {
        flashSignal(morse.charAt(j));
}
      delay(dotDuration * 3); 
    }
  }

  delay(5000); 
}

void flashSignal(char signal) {
  if (signal == '.') {
    digitalWrite(ledPin, HIGH);
    delay(dotDuration);
    digitalWrite(ledPin, LOW);
    delay(dotDuration); 
  } else if (signal == '-') {
    digitalWrite(ledPin, HIGH);
    delay(dotDuration * 3);
    digitalWrite(ledPin, LOW);
    delay(dotDuration);
  }
}

String morseCodeMap(char character) {
  if (character == 'a') return ".-";
  else if (character == 'b') return "-...";
  else if (character == 'c') return "-.-.";
  else if (character == 'd') return "-..";
  else if (character == 'e') return ".";
  else if (character == 'f') return "..-.";
  else if (character == 'g') return "--.";
  else if (character == 'h') return "....";
  else if (character == 'i') return "..";
  else if (character == 'j') return ".---";
  else if (character == 'k') return "-.-";
  else if (character == 'l') return ".-..";
  else if (character == 'm') return "--";
  else if (character == 'n') return "-.";
  else if (character == 'o') return "---";
  else if (character == 'p') return ".--.";
  else if (character == 'q') return "--.-";
  else if (character == 'r') return ".-.";
  else if (character == 's') return "...";
  else if (character == 't') return "-";
  else if (character == 'u') return "..-";
  else if (character == 'v') return "...-";
  else if (character == 'w') return ".--";
  else if (character == 'x') return "-..-";
  else if (character == 'y') return "-.--";
  else if (character == 'z') return "--..";
  else if (character == '1') return ".----";
  else if (character == '2') return "..---";
  else if (character == '3') return "...--";
  else if (character == '4') return "....-";
  else if (character == '5') return ".....";
  else if (character == '6') return "-....";
  else if (character == '7') return "--...";
  else if (character == '8') return "---..";
  else if (character == '9') return "----.";
  else if (character == '0') return "-----";
  else return "";
}
