import processing.serial.*;

Serial MySerial;
boolean Estate = false;
void setup() {
  size(400, 600);
  MySerial = new Serial(this, "/dev/ttyACM0", 9600);
}

void draw() {
  if (Estate) {
    background(255, 0, 0);
    fill(0, 100, 100);
  } else {
    background(0, 255, 0);
    fill(0, 0, 0);
  }
  ellipse(200, 200, 300, 300);
}

void mouseClicked() {
  float D = dist(mouseX, mouseY, 200, 200);
  if (D < 150) {
    MySerial.write('a');
    Estate = !Estate;
  }
}