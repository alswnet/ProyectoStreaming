let videoUSB;
let ModeloMobileNet;
let tipo = "No se";

function setup() {
  createCanvas(640, 480);
  VideoUSB = createCapture(VIDEO);
  VideoUSB.hide();
  ModeloMobileNet = ml5.imageClassifier('MobileNet', VideoUSB, ModeloListo);
}

function ModeloListo() {
  console.log("Modelo Listo :D");
  ModeloMobileNet.predict(OptenerPrediccion);
}

function OptenerPrediccion(error, results) {
  if (error) {
    console.log("Hay un error");
  } else {
    tipo = results[0].className;
    ModeloMobileNet.predict(OptenerPrediccion);
  }
}

function draw() {
  background(0);
  image(VideoUSB, 0, 0);
  fill(0, 255, 0);
  textSize(40);
  text(tipo, 10, height - 20);
}
