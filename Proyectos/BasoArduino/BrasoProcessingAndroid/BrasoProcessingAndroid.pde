//import processing.serial.*; //<>//

//Serial MiSerial;
int CantidadMotores = 6;
int Ancho;
int Alto;
int InicioCanvas;
int FinCanvas;
float[] Angulo = new float[CantidadMotores];
float[] AnguloEnviado = new float[CantidadMotores];
String NombrePuerto = "/dev/ttyACM0"; 
//Ver Arduino IDE para cambiar el puerto
//En Windos ej /COM3 
//En Lonux ej /dev/ttyUSB0

void setup() {
  fullScreen();
  Ancho =  width;
  Alto = height;
  InicioCanvas = 0 + Ancho/20;
  FinCanvas = Ancho - Ancho/20;
  for (int i = 0; i<CantidadMotores; i++) {
    Angulo[i] = 90;
    AnguloEnviado[i] = 90;
  }
  textAlign(CENTER);
  //MiSerial = new Serial(this, NombrePuerto, 9600);
}

void draw() {
  background(240);
  DibujarCuadros();
  DibujarLineas();
  DibujarNumeros();
  EnviarDatos();
}

void mouseDragged() {
  mouseClicked();
}

void mouseClicked() {
  int AnchoCelda = Alto/(CantidadMotores+1);
  for (int i = 0; i<CantidadMotores; i++) {
    if (mouseY<(i+1)*AnchoCelda) {
      Angulo[i] = map(mouseX, InicioCanvas, FinCanvas, 0, 180);
      Angulo[i] = int(constrain(Angulo[i], 0, 180));
      return;
    }
  }
}


void EnviarDatos() {
  if (!mousePressed) {
    for (int i = 0; i <CantidadMotores; i++) {
      if (Angulo[i] != AnguloEnviado[i]) {
        //MiSerial.write("M"+i+"T"+int(Angulo[i]));
        println("M"+i+"T"+int(Angulo[i]));
        AnguloEnviado[i] = Angulo[i];
      }
    }
  }
}