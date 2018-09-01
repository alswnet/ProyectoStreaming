float[] Valores;

int SuperI = 0;
int SuperJ = SuperI +1;
int CantidadLineas;//= widt;

void setup() {
  //size(600, 300);
  fullScreen();
  CantidadLineas = width;
  Valores = new float[ CantidadLineas];
  for (int i = 0; i< CantidadLineas; i++) {
    Valores[i] = random(100);
  }
  colorMode(HSB, 100);
  noStroke();

  /*for (int i = 0; i< 600; i++) {
   for (int j = i +1; j< 600; j++) {
   if (Valores[i] > Valores[j]) {
   float ValorTMP =  Valores[i];
   Valores[i] = Valores[j];
   Valores[j] = ValorTMP;
   }
   }
   }*/

  frameRate(120);
}

void draw() {
  background(0);
  for (int i = 0; i<  CantidadLineas; i++) {
    fill(Valores[i], 100, 100);
    rect(i, 0, 1, Valores[i]*(height/100));
  }

  for (int j =  SuperI + 1; j<  CantidadLineas; j++) {
    if (Valores[SuperI] > Valores[j]) {
      float ValorTMP =  Valores[SuperI];
      Valores[SuperI] = Valores[j];
      Valores[j] = ValorTMP;
    }
  }
  SuperI++;
}

void mouseClicked() {
  for (int i = 0; i< CantidadLineas; i++) {
    Valores[i] = random(100);
  }
  SuperI= 0;
}
