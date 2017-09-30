float EspacioBoton = Alto/8;

void DibujarCuadros() {
  noStroke();
                  //= Alto - Alto/7;
                  //= (CantidadMotores*(Alto-EspacioBoton))/(CantidadMotores+1))*;
                  //= ((A - A/8)/CM+1)*CM
                  //  9*A*CM/(8*CM+8)
                  // (CM * A - CM * E)/ (CM +1)
  float AltoBarra = (Alto-EspacioBoton)/(CantidadMotores+1);
  //Dibujar Fondo negro y recuadro blanco

  fill(0);
  rect(0, 0, Ancho, Alto);
  fill(250);
  rect(InicioCanvas, 0, AnchoCanvas, AltoBarra*CantidadMotores);

  for (int i = 0; i < CantidadMotores; i++) {
    color Fondo = ColorAurora(Angulo[i]);
    fill(Fondo);
    float AnchoBarra =  map(Angulo[i], 0, 180, 0, AnchoCanvas);
    rect(InicioCanvas, AltoBarra*i, AnchoBarra, AltoBarra);
  }
}

color ColorAurora(float V) {
  float ColorRojo = map(V, 0, 90, 255, 0);
  ColorRojo = constrain(ColorRojo, 0, 255);
  float ColorAzul = map(V, 90, 180, 0, 255);
  ColorAzul = constrain(ColorAzul, 0, 255);
  float ColorVerde = 255- ColorRojo- ColorAzul;
  ColorVerde = constrain(ColorVerde, 0, 255);
  color Fondo = color(ColorRojo, ColorVerde, ColorAzul);
  return Fondo;
}

void DibujarLineas() {
  float AltoRectangulo = (Alto-EspacioBoton)/(CantidadMotores+1);
  float AltoMaximo = Alto - Alto/7;
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
  float TamanoFuente = 30*displayDensity;
  textSize(TamanoFuente);

  float PosicionY = (Alto-EspacioBoton)/(CantidadMotores+1);
  for (int i = 0; i < CantidadMotores; i++) {
    float PosicionX =  map(Angulo[i], 0, 180, InicioCanvas, FinCanvas) + 10;
    if (Angulo[i] > 135) {
      PosicionX -= 80*displayDensity;
    }
    text(int(Angulo[i])+"⁰", PosicionX, i*PosicionY+PosicionY/2);
  }
}