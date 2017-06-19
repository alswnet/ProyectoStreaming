//#include "EmonLib.h"                   // Include Emon Library
//EnergyMonitor emon1;                   // Create an instance
//
//void setup()
//{
//  Serial.begin(9600);
//
//  emon1.current(5, 60);             // Current: input pin, calibration.
//  //calibration is explained bellow
//}
//
//void loop()
//{
//  double Irms = emon1.calcIrms(1480);  // Calculate Irms only
//
//  Serial.print(Irms*230.0);         // Apparent power
//  Serial.print(" ");
//  Serial.println(Irms);          // Irms
//}


int medida = 0;
void setup(){
  Serial.begin(9600);
}
void loop(){
  medida = analogRead(A1);
  Serial.println(medida);
  delay(300);
}

