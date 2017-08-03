import processing.serial.*;

Serial MiSerial;

void setup() {
  size(400, 600);
  String NombrePuerto = "/dev/ttyUSB0";
  MiSerial = new Serial(this, NombrePuerto, 9600);
}

void draw() {
  background(020, 100,100);
  fill(200,0,0);
  ellipse(200, 200, 300, 300);
  
}