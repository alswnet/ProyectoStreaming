#include <IRremote.h>

int PinIR = 11;

decode_results Respuesta;
int PinLed = 13;
boolean Estado = false;
IRrecv SensorIR(PinIR);

void setup() {
  Serial.begin(9600);
  pinMode(PinLed, OUTPUT);
  SensorIR.enableIRIn();
}

void loop() {
  if (SensorIR.decode(&Respuesta)) {
    if (Respuesta.value == 0x10EFD827) {
      Estado = !Estado;
      digitalWrite(PinLed, Estado);
    }
    Serial.println(Respuesta.value, HEX);
    SensorIR.resume();
  }
  delay(200);
}
