import controlP5.*;
import processing.serial.*;

ControlP5 cp5;
Serial MiSerial;


void setup() {
  size(400, 600);

  String NombrePuerto ="/dev/ttyUSB0";
  MiSerial = new Serial(this, NombrePuerto, 9600);
  cp5 = new ControlP5(this);

  cp5.addButton("Enviar")
    .setPosition(10, 10)
    .setSize(100, 40);
  ;
}

void draw() {
  background(255);
}

void Enviar() {
  MiSerial.write('a');
}