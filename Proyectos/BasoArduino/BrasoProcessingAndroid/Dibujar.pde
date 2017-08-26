
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
    float AnchoCuadro =  map(Angulo[i], 0, 180, InicioCanvas, FinCanvas);
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