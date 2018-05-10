const TelegramBot = require('node-telegram-bot-api');
const token = '391390577:AAFbqpHmY8bCz7GpMoQ9EKYljxViSI2frUs';

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
  }
  else if(Mensaje == "Apagar1"){
    bot.sendMessage(chatId, 'Apagando Lugar 1');
    port.write('b');
  }

});
