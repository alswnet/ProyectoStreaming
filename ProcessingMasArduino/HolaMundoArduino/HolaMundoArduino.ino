int PinLed = 5;
boolean EstadoLed = false;

void setup() {
  Serial.begin(9600);
  pinMode(PinLed, OUTPUT);
  digitalWrite(PinLed, EstadoLed);
}

void loop() {
  if (Serial.available()) {
    char Letra = Serial.read();
    if (Letra == 'a') {
      EstadoLed = !EstadoLed;
    }
  digitalWrite(PinLed, EstadoLed);
  }
}
