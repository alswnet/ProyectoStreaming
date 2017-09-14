void setup() {
  fullScreen();
  Iniciar();
}

void draw() {
  if (SePuedeDibujar()) {
    // TU CODIGO DIBUJO
    
    // HASTA AQUI CODIGO DIBUJO
  }
}

void mouseReleased() {
  if (SePuedePresionar()) {
    // TU CODIGO MOUSE
    
    // HASTA AQUI CODIGO MOUSE
  }
}

//EstaAvilitada() - boolean - Para ver si hay datos seriales - 
//PedirString() - string - Para pedir un string con lo que tenga el puerto hasta el puerto
//PedirChar() - char -Para pedir un char del string 
//PedirInt() - int - Para pedir un int del arduino
//Enviar(String) - Envia un String
//Enviar(int) - Envia un String