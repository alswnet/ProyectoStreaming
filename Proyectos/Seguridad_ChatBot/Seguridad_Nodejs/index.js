const TelegramBot = require('node-telegram-bot-api');
const token = '585564286:AAFtIlbHvY-NzF9hX7WSsn7zf0dMFfIYRfY';

var SerialPort = require('serialport');
var port = new SerialPort('/dev/ttyUSB0', {
  baudRate: 9600
});

const bot = new TelegramBot(token, {
  polling: true
});
var IdSecreto = 30085334;

bot.on('message', (msg) => {
  const chatId = msg.chat.id;
  var Mensaje = msg.text;
  if (Mensaje == "Apagar") {
    bot.sendMessage(chatId, 'Se apago la alarma');
    port.write("A");
  } else if (Mensaje == "Encender") {
    bot.sendMessage(chatId, 'Encender la alarma');
    port.write("E");
  }
  console.log("El chatid es " + chatId);
});


port.setEncoding('utf8');

port.on('data', function(data) {
  console.log("Lo que entro es " + data);
  if (data[0] == 'A') {
    console.log("Boton Precionado");
    bot.sendMessage(IdSecreto, "Entro alguin ten cuidado");
  }
});
