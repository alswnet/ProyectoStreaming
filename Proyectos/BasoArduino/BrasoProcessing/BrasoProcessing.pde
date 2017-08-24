import processing.serial.*;

Serial MiSerial;
int CantidadMotores = 6;
int Ancho;
int Alto;
float[] Angulo = new float[CantidadMotores];
float[] AnguloEnviado = new float[CantidadMotores];
String NombrePuerto = "/dev/ttyUSB0"; 
//Ver Arduino IDE para cambiar el puerto
//En Windos ej /COM3 
//En Lonux ej /dev/ttyUSB0


void setup() {
  size(400, 600);
  Ancho =  width;
  Alto = height;
  for (int i = 0; i<CantidadMotores; i++) {
    Angulo[i] = 90;
    AnguloEnviado[i] = 90;
  }
  textAlign(CENTER);
  //MiSerial = new Serial(this, "/dev/ttyUSB0", 9600);
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
      Angulo[i] = map(mouseX, 0, Ancho, 0, 180);
      Angulo[i] = int(constrain(Angulo[i], 0, 180));
      return;
    }
  }
}

void DibujarNumeros() {

  fill(255, 0, 0, 200);
  textAlign(LEFT, CENTER);
  textSize(40);

  int PosicionY = Alto/(CantidadMotores+1);
  for (int i = 0; i < CantidadMotores; i++) {
    float PosicionX =  map(Angulo[i], 0, 180, 0, Ancho)+10;
    if (Angulo[i] > 135)
      PosicionX -= Ancho/4;
    text(int(Angulo[i])+"⁰", PosicionX, i*PosicionY+PosicionY/2);
  }
}

void DibujarCuadros() {
  noStroke();
  int AltoCuadro = Alto/(CantidadMotores+1);
  for (int i = 0; i<CantidadMotores; i++) {
    float ColorRojo = map(Angulo[i], 0, 90, 255, 0);
    ColorRojo = constrain(ColorRojo, 0, 255);
    float ColorAzul = map(Angulo[i], 90, 180, 0, 255);
    ColorAzul = constrain(ColorAzul, 0, 255);
    float ColorVerde = 255- ColorRojo- ColorAzul;
    ColorVerde = constrain(ColorVerde, 0, 255);
    color Fondo = color(ColorRojo, ColorVerde, ColorAzul);
    fill(Fondo);
    float AnchoCuadro =  map(Angulo[i], 0, 180, 0, Ancho);
    rect(0, AltoCuadro*i, AnchoCuadro, AltoCuadro);
  }
}

void DibujarLineas() {
  int AltoRectangulo = Alto/(CantidadMotores+1);
  int AltoMaximo = Alto - Alto/(CantidadMotores+1);
  strokeWeight(10); 
  stroke(0);
  for (int i = 0; i <=CantidadMotores; i++) {
    line(0, i*AltoRectangulo, Ancho, i*AltoRectangulo );
  }
  strokeWeight(1);
  stroke(100);
  for (int i = 1; i< 18; i++) {
    float AnchoRectangulo = map(i, 0, 18, 0, Ancho);
    line(AnchoRectangulo, 0, AnchoRectangulo, AltoMaximo);
  }
  strokeWeight(6); 
  stroke(50, 50);
  for (int i = 1; i< 4; i++) {
    float AnchoRectangulo = map(i, 0, 4, 0, Ancho);
    line(AnchoRectangulo, 0, AnchoRectangulo, AltoMaximo);
  }
  strokeWeight(10); 
  stroke(50);
  for (int i = 1; i< 2; i++) {
    float AnchoRectangulo = map(i, 0, 2, 0, Ancho);
    line(AnchoRectangulo, 0, AnchoRectangulo, AltoMaximo);
  }
}

void EnviarDatos() {
  if (!mousePressed) {
    for (int i = 0; i <CantidadMotores; i++) {
      if (Angulo[i] != AnguloEnviado[i]) {
        // MiSerial.write("M"+i+"T"+int(Angulo[i]));
        println("M"+i+"T"+int(Angulo[i]));
        AnguloEnviado[i] = Angulo[i];
      }
    }
  }
}