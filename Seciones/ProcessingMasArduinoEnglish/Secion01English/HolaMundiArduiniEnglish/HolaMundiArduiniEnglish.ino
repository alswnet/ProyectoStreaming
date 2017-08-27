int PinLed = 13;
boolean Estado = false;
void setup() {
  pinMode(PinLed, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    char Data = Serial.read();
    Estado = !Estado;
    if (Estado) {
      digitalWrite(PinLed, 1);
    }
    else {
      digitalWrite(PinLed, 0);
    }
  }
}
