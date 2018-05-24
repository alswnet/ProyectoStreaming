const TelegramBot = require('node-telegram-bot-api');
const token = 'xxx';

var SerialPort = require('serialport');
var port = new SerialPort('/dev/ttyUSB0', {
  baudRate: 9600
});

const bot = new TelegramBot(token, {
  polling: true
});

bot.on('message', (msg) => {
  const chatId = msg.chat.id;
  var Mensaje = msg.text;
  if (Mensaje == "Encender1") {
    bot.sendMessage(chatId, 'Encendiendo Lugar 1');
    port.write('a');
  } else if (Mensaje == "Apagar1") {
    bot.sendMessage(chatId, 'Apagando Lugar 1');
    port.write('b');
  }
  if (Mensaje == "Encender2") {
    bot.sendMessage(chatId, 'Encendiendo Lugar 2');
    port.write('c');
  } else if (Mensaje == "Apagar2") {
    bot.sendMessage(chatId, 'Apagando Lugar 2');
    port.write('d');
  }
  if (Mensaje == "Encender3") {
    bot.sendMessage(chatId, 'Encendiendo Lugar 3');
    port.write('e');
  } else if (Mensaje == "Apagar3") {
    bot.sendMessage(chatId, 'Apagando Lugar 3');
    port.write('f');
  }
  if (Mensaje == "Encendertodo") {
    bot.sendMessage(chatId, 'Encendiendo todas las luses');
    port.write('a');
    port.write('b');
    port.write('c');
  } else if (Mensaje == "Apagartodo") {
    bot.sendMessage(chatId, 'Apagando todas las luses');
    port.write('b');
    port.write('e');
    port.write('f');
  }
});
