#include "EmonLib.h"//Librerias de Emom
EnergyMonitor SensorEmon;//                   // Create an instance

void setup()
{
  Serial.begin(9600);
  SensorEmon.current(1, 60.1); //Pin de entrada, valor de calibracion
}

void loop()
{
  double Coriente = SensorEmon.calcIrms(1480);  // Calcular la Corriete
  Serial.print("La corriente: ");
  Serial.print(Coriente);//Imprimir corriente
  Serial.print(" Potencia: ");
  Serial.println(Coriente * 120);
}

