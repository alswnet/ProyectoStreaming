const TelegramBot = require('node-telegram-bot-api');
var mqtt = require('mqtt');
const fs = require('fs');
var Estado = 0;
const token = '520821559:AAHYQSi0MiXtQlckbkkO8oqSye7BZoMGeG0';
const bot = new TelegramBot(token, {
  polling: true
});
var client = mqtt.connect('mqtt://broker.mqtt-dashboard.com')

bot.on('message', (msg) => {
  const chatId = msg.chat.id;
  var mensaje = msg.text;

  console.log("Mensaje es :" + mensaje);
  if (Estado == 0) {
    if (mensaje == "Hola" || mensaje == "Ayuda") {
      bot.sendMessage(chatId, 'Listo para empezar a usar la alarma, comandos EncenderAlarma o ApagarAlarma');
    } else if (mensaje == "EncenderAlarma") {
      bot.sendMessage(chatId, 'activando alarma');
<<<<<<< HEAD
      client.publish('AlarmaActiva', 1);
    } else if (mensaje == "ApagarAlarma") {
      bot.sendMessage(chatId, 'Apagando alarma');
      client.publish('AlarmaActiva', 0);
=======
      client.publish('EstadoAlarmaALSW', '1');
    } else if (mensaje == "ApagarAlarma") {
      bot.sendMessage(chatId, 'Apagando alarma');
      client.publish('EstadoAlarmaALSW', '0');
>>>>>>> 398204e1d5ce918b3beb8ed1b6e1a83edb6d92ba
    } else if (mensaje == "Programar") {
      bot.sendMessage(chatId, 'A que hora quiere programarlo:');
      Estado = 1;
    } else if (mensaje == "Preguntar") {
      fs.readFile('./hora.cvs', function leer(erro, data) {
        bot.sendMessage(chatId, 'Alarma Programada para ' + data);
        console.log(data + " Id " + chatId);
      });
    } else if (mensaje == "Estado") {
      bot.sendMessage(chatId, 'No se');
    }
  } else if (Estado == 1) {
    fs.writeFile('./hora.cvs', mensaje, function(err) {
      console.log("Salvado");
      bot.sendMessage(chatId, 'Alarma guarda consulta con Preguntar');
      Estado = 0;
    })
  }
});

client.on('connect', function() {
<<<<<<< HEAD
  console.log("Activado Mqtt")
  client.subscribe('EstadoAlarmaALSW', function(err) {
  })
})
=======
  client.subscribe('EstadoAlarmaALSW', function(err) {
    if (!err) {
      client.publish('EstadoAlarmaALSW', 'Hello mqtt')
    }
  })
})

client.on('message', function(topic, message) {
  // message is Buffer
  console.log(message.toString())
})
>>>>>>> 398204e1d5ce918b3beb8ed1b6e1a83edb6d92ba
