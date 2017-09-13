int Sensor = A3;
int LoMas = 4;
int LoMenos = 5;


void setup() {
  pinMode(A3, INPUT);
  pinMode(LoMas, INPUT);
  pinMode(LoMenos, INPUT);
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(LoMAs) == 1 || digitalRead(LoMenos) == 1) {
    serial.println(1024 / 2);
  }
  else {
    int ValorSensor = analogRead(Sensor);
    Serial.println(ValorSensor);
  }
}
