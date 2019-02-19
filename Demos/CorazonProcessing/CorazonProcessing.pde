float r = 300;
float cantidad = 150;
float factor = 2;

void setup() {
  //size(800, 800);
  fullScreen();
  r = height*0.4;
}

void draw() {

  cantidad  = map(mouseX, 0, width, 1, 300);
  factor = (map(mouseY, 0, height, 1, 5));

  background(200, 0, 0);
  translate(width/2, height/2);
  fill(255);
  circle(0, 0, r*2);
  fill(0, 200, 0);
  for (int i = 0; i < cantidad; i++) {
    PVector Circulo = BuscarCirculo(i, cantidad);
    circle(Circulo.x, Circulo.y, 20);
  }

  strokeWeight(4);
  for (int i = 0; i < cantidad; i++) {
    PVector P1 = BuscarCirculo(i, cantidad);
    PVector P2 = BuscarCirculo(i*factor, cantidad);
    line(P1.x, P1.y, P2.x, P2.y);
  }
}

PVector BuscarCirculo(float i, float Total) {
  float Angulo = map(i % Total, 0, Total, 0, TWO_PI);
  PVector Vector = PVector.fromAngle(Angulo);
  Vector.mult(r);
  return Vector;
}
