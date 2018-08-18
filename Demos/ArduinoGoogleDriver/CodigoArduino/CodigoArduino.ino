int Boton = 2;
int Led = 13;

void setup() {
  Serial.begin(9600);
  pinMode(Boton, INPUT_PULLUP);
  pinMode(Led, OUTPUT);
}

void loop() {
  if (digitalRead(Boton) == 0) {
    Serial.println("K");
    delay(500);
  }

  if (Serial.available()) {
    char Letra = Serial.read();
    if (Letra == 'H') {
      digitalWrite(Led, 1);
    } else if (Letra == 'L') {
      digitalWrite(Led, 0);
    }
  }

}
