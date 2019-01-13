
class Particula {

  PVector Posicion;
  float Radio;
  color Color;

  Particula(float x_, float y_) {
    Posicion = new PVector(x_, y_);
    Radio = 5;
    Color = color(random(0, 255), random(0, 255), random(0, 255));
  }

  void Dibujar() {
    fill(Color);
    ellipse(Posicion.x, Posicion.y, Radio *2, Radio *2);
  }

  void Mover() {
    Posicion.x = Posicion.x - 1;
    Posicion.y = Posicion.y + random(-1, 1);

    float Angulo = Posicion.heading();
    Angulo = constrain(Angulo, 0, PI/6);
    Color = color(map(Angulo, 0, PI/6, 0, 255), 0, map(Angulo, 0, PI/6, 255, 0));
    float Mangitud = Posicion.mag();
    Posicion = PVector.fromAngle(Angulo);
    Posicion.setMag(Mangitud);
  }

  boolean Choque(ArrayList<Particula> CopoBebe) {
    for (Particula BebeParticula : CopoBebe) {
      float D = dist(BebeParticula.Posicion.x, BebeParticula.Posicion.y, Posicion.x, Posicion.y);
      if (D < Radio*1.8 ) {
        return true;
      }
    }
    return false;
  }

  boolean Final() {
    boolean Llego = Posicion.x < 1;
    return Llego;
  }
}
