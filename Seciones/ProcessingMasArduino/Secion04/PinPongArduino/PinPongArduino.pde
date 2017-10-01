import processing.serial.*; 

float[] PosicionJugador = {0, 0};
float[] PuntoJugador = {0, 0};
float[] PosicionBola;
float[] Velocidad;
float VelocidadMaxima = 25;
float Aceleracion;// = 0.1;

float RadioBola = 20;

float AnchoBarra;// = height/5;
float GrosorBarra;// = AnchoBarra/3;
Serial Serial1;  

void setup() {
  size(900, 500);
  Velocidad = new float[2];
  PosicionBola = new float[2];
  noStroke();
  AnchoBarra = height/5;
  GrosorBarra = AnchoBarra/3;
  IniciarBola();
}


void draw() {
  background(0);
  ActualizarBola();
  DibujarBarra();
  DibujarBola();
  DibujarMarcador();
}

void DibujarMarcador() {
  textSize(80);  
  textAlign(CENTER);
  text(int(PuntoJugador[0])+" : "+int(PuntoJugador[1]), width/2, height/6);
}

void serialEvent(Serial p) { 
  if (Serial1  == p)
    print ("hol");
  // String inString = p.readString();
} 

void RebotarY() {
  if (PosicionBola[1] - RadioBola < 0 || PosicionBola[1] + RadioBola > height) {
    Velocidad[1] = -Velocidad[1];
  }
}

void AumentarPuntos() {
  if (PosicionBola[0] - RadioBola < 0) {
    PuntoJugador[1]++;
    IniciarBola();
  } else if (PosicionBola[0] - RadioBola > width) {
    PuntoJugador[0]++;
    IniciarBola();
  }
}

void ActualizarBola() {
  RebotarY();
  RebotarBarra();
  AumentarPuntos();
  MoverBola();
}

void MoverBola() {
  for (int i = 0; i<2; i++) {
    PosicionBola[i] += Velocidad[i];
  }
}

void RebotarBarra() {
  if ((PosicionBola[1] > PosicionJugador[0] && PosicionJugador[0] < PosicionBola[1] + AnchoBarra ) &&
    (PosicionBola[0] - RadioBola < GrosorBarra || PosicionBola[0] +RadioBola > width - GrosorBarra )) {

    Aceleracion = -Aceleracion;
    if (abs(Velocidad[0]) < VelocidadMaxima) {
      Velocidad[0] = -Velocidad[0] + Aceleracion;
    } else {
      Velocidad[0] = -Velocidad[0];
    }
    println(Velocidad[0]);
  }
}

void IniciarBola() {
  PosicionBola[0] = width/2;
  PosicionBola[1] = height/2;
  Velocidad[0] = -3;
  Velocidad[1] = 0;
  Aceleracion = -2;
  MoverBarra(0, 50);
  MoverBarra(1, 50);
}

void DibujarBola() {
  ellipse(PosicionBola[0], PosicionBola[1], RadioBola*2, RadioBola*2);
}


void MoverBarra(int Jugador, float Rango) {
  if (Rango >= 0 && Rango <= 100) {
    Rango = map(Rango, 0, 100, 0, height- AnchoBarra);
    PosicionJugador[Jugador] = Rango;
  }
}


void DibujarBarra() {
  fill(200, 0, 0);
  for (int i = 0; i<2; i++) {
    if (i == 1) {
      rect(0, PosicionJugador[i], GrosorBarra, AnchoBarra);
    } else if (i == 0) {
      rect(width-GrosorBarra, PosicionJugador[i], GrosorBarra, AnchoBarra);
    }
  }
}