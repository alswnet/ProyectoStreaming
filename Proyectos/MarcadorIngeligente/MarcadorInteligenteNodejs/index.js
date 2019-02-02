var mqtt = require('mqtt')
var client = mqtt.connect('mqtt://broker.mqttdashboard.com')

var GoogleSpreadsheet = require('google-spreadsheet');
var async = require('async');

var doc = new GoogleSpreadsheet('1aaGFZfLEnKhtyhe3-0r7k1gxzXX4e5w07-YVE75Cqq8');
var sheet;
var creds = require('./ContrasenaApi.json');//Descarga las ruta de console.google

doc.useServiceAccountAuth(creds, ActivandoGoogleDoct);
var CantidadMinion = 6;

function ActivandoGoogleDoct() {
  console.log("Credenciar actividas");
  doc.getInfo(function(err, info) {
    console.log('Cargando documento: ' + info.title + ' de ' + info.author.email);
    var date = new Date();
    var Anno = date.getFullYear();
    var Mes = date.getMonth() + 1;
    var contador = 0;
    sheet = info.worksheets[0];
    //Buscar de hoja de mes/anno
    while (sheet.title != Mes + "/" + Anno) {
      contador++;
      sheet = info.worksheets[contador];
    }
    console.log("Hora activada:" + sheet.title);
  });

}

client.on('connect', function() {
  console.log("Conectado con mqtt");
  client.subscribe("ALSWEntrada");
  client.subscribe("ALSWSalida");
})
client.on('message', function(topic, message) {

  doc.getInfo(function(err, info) {
    console.log('Abiendo Archivo: ' + info.title + ' de ' + info.author.email);
    var date = new Date();
    var Anno = date.getFullYear();
    var Mes = date.getMonth() + 1;
    var contador = 0;
    sheet = info.worksheets[0];
    //Buscar de hoja de mes/anno
    while (sheet.title != Mes + "/" + Anno) {
      contador++;
      sheet = info.worksheets[contador];
    }
    console.log("Hora activada:" + sheet.title);
  });

  Listo = true;

  if (Listo) {
    // message is Buffer
    console.log("Informacion de " + topic + " usuario " + message.toString());

    var FechaActual = new Date();
    var Hora = FechaActual.getHours();
    var Minuto = FechaActual.getMinutes();
    var Segundo = FechaActual.getSeconds();
    var Dia = FechaActual.getDate();
    var ID = parseInt(message.toString());

    sheet.getCells({
      'min-row': 3,
      'max-row': 3 + 31,
      'min-col': 2,
      'max-col': 1 + CantidadMinion * 3,
      'return-empty': true
    }, function(err, cells) {

      var celda;
      if (topic.toString() == "ALSWEntrada") {
        celda = cells[(Dia - 1) * (CantidadMinion * 3) + ID * 3];
      } else if (topic.toString() == "ALSWSalida") {
        celda = cells[(Dia - 1) * (CantidadMinion * 3) + ID * 3 + 1];
      }
      celda.value = Hora + ":" + Minuto + ":" + Segundo;
      celda.save();
      console.log("Hora guarda: " + celda.value);

    });
  }
})
