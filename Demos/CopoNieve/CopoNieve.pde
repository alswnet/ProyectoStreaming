
Particula MiParticula;
ArrayList<Particula> CopoNieve;

void setup() {
  //size(600, 600);
  fullScreen();
  noStroke();
  MiParticula = new Particula(width/2, 0);
  CopoNieve = new ArrayList<Particula>();
}

void draw() {
  background(0);
  translate(width/2, height/2);

  Boolean Encontrado = false;
  while (!Encontrado) {
    MiParticula.Mover();
    //MiParticula.Dibujar();
    if (MiParticula.Final() || MiParticula.Choque(CopoNieve)) {
      CopoNieve.add(MiParticula);
      MiParticula = new Particula(width, random(0, height/2));
      Encontrado = true;
    }
  }
  for (int i = 0; i < 6; i++) {
    rotate(PI/3);
    for (Particula BebeParticula : CopoNieve) {
      BebeParticula.Dibujar();
    }
    pushMatrix();
    scale(1, -1);
    for (Particula BebeParticula : CopoNieve) {
      BebeParticula.Dibujar();
    }

    popMatrix();
  }
}

void keyPressed() {
  if (key == 'k') {
    CopoNieve = new ArrayList<Particula>();
  }
}
