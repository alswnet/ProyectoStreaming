#include <Wire.h>//Include the Wire library to talk I2C

#define MCP4725_ADDR 0x60

float x1 = 0.0;
float y1 = 0.0;
float x2 = 200.0;
float y2 = 0.0;

boolean pendiente = true;

int salida = 0;

void setup() {
  Wire.begin();
  Serial.begin(9600);
}

void loop () {
  if(pendiente) {
    y1 = x1;
    x1++;
    salida = y1;
    if (y1 == 200) {
      pendiente = false;
      x1 = 0;
      y1 = 0;
    }
  }
  else {
    y2 = x2;
    x2--;
    if (y2 == 0) {
      pendiente = true;
      x2 = 200;
      y2 = 0;
    }
    salida = y2;
  }
  Wire.beginTransmission(MCP4725_ADDR);
  Wire.write(64);                     // cmd to update the DAC
  Wire.write(salida >> 4);        // the 8 most significant bits...
  Wire.write((salida & 15) << 4); // the 4 least significant bits...
  Wire.endTransmission();
  delay(1*int(analogRead(A2)));
  Serial.println(salida);
}

