let Video;
let Neurona;

function setup() {
  noCanvas();
  console.log("iniciando");
  video = createCapture(VIDEO).parent('video');
  Neurona = new ml5.KNNImageClassifier(2, 1, CargarModelo, video.elt);
  //Neurona.load('inteligencia.json', updateExampleCounts);

  BotonCosas1 = select('#cosas1');
  BotonCosas1.mousePressed(() => EntrenarCosas1());

  BotonCosas2 = select('#cosas2');
  BotonCosas2.mousePressed(() => EntrenarCosas2());

  BotonCosasNo = select('#cosasno');
  BotonCosasNo.mousePressed(() => EntrenarCosasNo());

  BotonEntrenar = select('#entrenar');
  BotonEntrenar.mousePressed(() => Entrenando());

  BotonSalvar = select('#salvar');
  BotonSalvar.mousePressed(() => Salvador());
}

function Salvador() {
  Neurona.save("test");

}

function Entrenando() {
  console.log("Empezando a Entrenar")
  Neurona.predictFromVideo(ClasificarImagen);
}

function ClasificarImagen(Resultado) {
  let Mensaje;
  if (Resultado.classIndex == 1) {
    Mensaje = "Cosas1";

  }
  if (Resultado.classIndex == 2) {
    Mensaje = "Cosas2";

  }
  if (Resultado.classIndex == 3) {
    Mensaje = "No Cosas";

  }
  select('#prediccion').html(Mensaje)
  setTimeout(function() {
    Entrenando();
  }, 50);
}

function EntrenarCosas1() {
  console.log("Entrenar Cosas 1 ");
  Neurona.addImageFromVideo(1);
}

function EntrenarCosas2() {
  console.log("Entrenar Cosas 2 ");
  Neurona.addImageFromVideo(2);
}

function EntrenarCosasNo() {
  console.log("Entrenar Cosas No ");
  Neurona.addImageFromVideo(3);
}

function CargarModelo() {
  console.log("Modelo Cargado");
}
