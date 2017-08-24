import processing.serial.*;

Serial MiSerial;
int CantidadMotores = 3;
int Ancho = 400;
int Alto = 600;
float[] Angulo = {0, 0, 0};
float[] AnguloEnviado = {0, 0, 0};
void setup() {
  size(400, 600);
  MiSerial = new Serial(this, "/dev/ttyUSB0", 9600);
}

void draw() {
  background(250);
  for (int i = 0; i <CantidadMotores; i++) {
    line(0, i*(Alto/3), Ancho, i*(Alto/3) );
  }
  for (int i = 1; i< 45; i++) {
    line(map(i, 0, 45, 0, Ancho), 0, map(i, 0, 45, 0, Ancho), Alto);
  }
  fill(100, 100, 0);
  rect(0, 0, map(Angulo[0], 0, 180, 0, Ancho), Alto/3);
  fill(0, 100, 100);  
  rect(0, Alto/3, Angulo[1]*(Ancho/180), Alto/3);
  fill(100, 0, 100);
  rect(0, 2*Alto/3, Angulo[2]*(Ancho/180), Alto/3);
  textSize(50);
  textAlign(CENTER, CENTER);
  fill(255, 0, 0);
  text(int(Angulo[0]), Ancho/2, (Alto*1)/6);
  text(int(Angulo[1]), Ancho/2, (Alto*3)/6);
  text(int(Angulo[2]), Ancho/2, (Alto*5)/6);

  for (int i = 0; i <3; i++) {
    if (Angulo[i] != AnguloEnviado[i]) {
      MiSerial.write("M"+i+"T"+int(Angulo[i]));
      AnguloEnviado = Angulo;
    }
  }
}

void mousePressed() {
  for (int i = 0; i<3; i++) {
    if (mouseY<(i+1)*Alto/3) {
      Angulo[i] = map(mouseX, 0, Ancho, 0, 180);
      return;
    }
  }
}

void mouseClicked() {
  mousePressed();
}