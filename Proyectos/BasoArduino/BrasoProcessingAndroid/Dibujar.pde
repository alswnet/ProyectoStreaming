
void DibujarCuadros() {
  noStroke();
  int AltoCuadro = Alto/(CantidadMotores+1);
  //Dibujar Fondo negro y recuadro blanco
  if (EstadoBT == 2) {
   fill(0);
  } else if (EstadoBT == 1) {
    fill(100);
  } else {
    fill(200);
  }
  rect(0, 0, Ancho, Alto);
  fill(250);
  rect(InicioCanvas, 0, AnchoCanvas, AltoCuadro*CantidadMotores);

  for (int i = 0; i<CantidadMotores; i++) {
    float ColorRojo = map(Angulo[i], 0, 90, 255, 0);
    ColorRojo = constrain(ColorRojo, 0, 255);
    float ColorAzul = map(Angulo[i], 90, 180, 0, 255);
    ColorAzul = constrain(ColorAzul, 0, 255);
    float ColorVerde = 255- ColorRojo- ColorAzul;
    ColorVerde = constrain(ColorVerde, 0, 255);
    color Fondo = color(ColorRojo, ColorVerde, ColorAzul);
    fill(Fondo);
    float AnchoCuadro =  map(Angulo[i], 0, 180, 0, AnchoCanvas);
    rect(InicioCanvas, AltoCuadro*i, AnchoCuadro, AltoCuadro);
  }
}

void DibujarLineas() {
  int AltoRectangulo = Alto/(CantidadMotores+1);
  int AltoMaximo = Alto - Alto/(CantidadMotores+1);
  strokeWeight(10); 
  stroke(0);
  //Dibujar Linea Vertical
  for (int i = 0; i <=CantidadMotores; i++) {
    line(InicioCanvas, i*AltoRectangulo, FinCanvas, i*AltoRectangulo );
  }
  strokeWeight(1);
  stroke(100);
  //Dibuja lineas cada 10 grados
  for (int i = 1; i< 18; i++) {
    float AnchoRectangulo = map(i, 0, 18, InicioCanvas, FinCanvas);
    line(AnchoRectangulo, 0, AnchoRectangulo, AltoMaximo);
  }
  strokeWeight(6); 
  stroke(200, 0, 0, 50);
  //Dibuja lineas cada 45 grados 
  for (int i = 1; i< 4; i++) {
    float AnchoRectangulo = map(i, 0, 4, InicioCanvas, FinCanvas);
    line(AnchoRectangulo, 0, AnchoRectangulo, AltoMaximo);
  }
  strokeWeight(10); 
  stroke(200, 0, 0);
  //Dibuja lineas cada 90 Grados
  for (int i = 0; i<= 2; i++) {
    float AnchoRectangulo = map(i, 0, 2, InicioCanvas, FinCanvas);
    line(AnchoRectangulo, 0, AnchoRectangulo, AltoMaximo);
  }
}


void DibujarNumeros() {

  fill(255, 0, 0, 200);
  textAlign(LEFT, CENTER);
  float TamanoFuente = map(AnchoCanvas, 500, 2000, 30, 80);
  textSize(TamanoFuente);

  int PosicionY = Alto/(CantidadMotores+1);
  for (int i = 0; i < CantidadMotores; i++) {
    float PosicionX =  map(Angulo[i], 0, 180, InicioCanvas, FinCanvas) + 10;
    if (Angulo[i] > 135) {
      PosicionX -= Ancho/9;
    }
    text(int(Angulo[i])+"⁰", PosicionX, i*PosicionY+PosicionY/2);
  }
}