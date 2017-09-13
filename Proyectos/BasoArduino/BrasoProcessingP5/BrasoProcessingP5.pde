import processing.serial.*;
import controlP5.*;

ControlP5 ControlP5;
int CantidadMotores = 6;
Serial MiSerial;

int Ancho;
int Alto;
String[] NombreAngulo = {"M0", "M1", "M2", "M3", "M4", "M5"};
float[] Angulo = new float[CantidadMotores];
float[] AnguloEnviado = new float[CantidadMotores];
String NombrePuerto = "/dev/ttyUSB0"; 


void setup() {
  size(400, 600);
  Ancho =  width;
  Alto = height;
  int AltoCuadro = Alto/(CantidadMotores+1);

  ControlP5 = new ControlP5(this);
  for (int i =0; i<CantidadMotores; i++) {
    ControlP5.addSlider(NombreAngulo[i])
      .setPosition(10, AltoCuadro*i+10)
      .setSize(Ancho-40, AltoCuadro-20)
      .setRange(0, 180)
      .setValue(90)
      ;
  }
  MiSerial = new Serial(this, NombrePuerto, 9600);
}

void draw() {
  ActrualizarValores();
  EnviarDatos();
}

void ActrualizarValores() {
  for (int i = 0; i < CantidadMotores; i++) {
    Angulo[i] = ControlP5.getController(NombreAngulo[i]).getValue();
  }
}


void EnviarDatos() {
  if (!mousePressed) {
    for (int i = 0; i <CantidadMotores; i++) {
      if (Angulo[i] != AnguloEnviado[i]) {
        MiSerial.write("M"+i+"T"+int(Angulo[i]));
        println("M"+i+"T"+int(Angulo[i]));
        AnguloEnviado[i] = Angulo[i];
      }
    }
  }
}