int Sensor = A0;

void setup() {
  pinMode(Sensor, INPUT);
  Serial.begin(9600);
}

void loop() {
  int Valor  = analogRead(Sensor);
  Serial.println(Valor);
  delay(100);
}
