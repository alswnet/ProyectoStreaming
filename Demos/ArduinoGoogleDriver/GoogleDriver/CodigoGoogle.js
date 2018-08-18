var SerialPort = require('serialport');
var port = new SerialPort('/dev/ttyUSB0', {
  baudRate: 9600
});

var GoogleSpreadsheet = require('google-spreadsheet');
var async = require('async');

var doc = new GoogleSpreadsheet('ID');
var sheet;

var creds = require('./TusCredenciales.json');

doc.useServiceAccountAuth(creds, intervalFunc);

async function intervalFunc() {
  console.log('Empezando!');
  await doc.getInfo(function(err, info) {
    console.log('Loaded doc: ' + info.title + ' by ' + info.author.email);
    sheet = info.worksheets[0];
  });

  sheet.getCells({
    'min-row': 1,
    'max-row': 3,
    'min-col': 1,
    'max-col': 3,
    'return-empty': true
  }, function(err, cells) {
    console.log("Celda " + cells[0].value);
    if (cells[0].value == "Encender") {
      port.write("H");
    } else if (cells[0].value == "Apagar") {
      port.write("L");
    }
    var celda = cells[1];
    celda.value = 1234;
    celda.save();
  });
}

setInterval(intervalFunc, 2000);
