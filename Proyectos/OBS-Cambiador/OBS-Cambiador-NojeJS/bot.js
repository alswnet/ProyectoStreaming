const OBSWebSocket = require('obs-websocket-js');
var SerialPort = require('serialport');
var portName = process.argv[2];
var MensajeSerial = "";
console.log("PueroUSB "+portName);

var OpcioneOBS = {
address: 'sakura.local:4444'
};

const obs = new OBSWebSocket();

obs.connect(OpcioneOBS)
.then( () => {
    return obs.GetStreamingStatus();
})
.then(data =>{
  console.log(data);
  if(data.recording == true){
    port.write('RT');
    console.log('Esta grabacion');
  }
  if(data.streaming == true){
    port.write('ET');
    console.log("Esta Striming");
  }
});

var OpcionSerial =  {
  baudRate: 9600,
  autoOpen: true
};

var port = new SerialPort(portName,OpcionSerial);

port.on('data', function (data) {

  console.log("Estasdo "+obs.GetCurrentTransition());

  for(var i = 0; i < data.length;i++){
    MensajeSerial  = MensajeSerial  + String.fromCharCode(data[i]);
  }
  console.log('Data:',MensajeSerial);
  if(MensajeSerial === "RT"){
    console.log("Orden Iniciar Grabacion");
    MensajeSerial = "";
    obs.StartRecording();
  }
  else if(MensajeSerial === "RF"){
    console.log("Orden Terminando Grabacion");
    MensajeSerial = "";
    obs.StopRecording();
  }
  else if(MensajeSerial == "ET"){
    console.log("Orden Iniciar Termision");
    MensajeSerial = "";
    obs.StartStreaming();
  }
  else if(MensajeSerial == "EF"){
    console.log("Orden Cancelar Termision");
    MensajeSerial = "";
    obs.StopStreaming();
  }
});

obs.on('RecordingStarted',err => {
  port.write('RT');
  console.log('Iniciando grabacion:');
});

obs.on('RecordingStopping',err => {
    port.write('RF');
    console.log('Terminando grabacion:');
});

obs.on('StreamStarting', dato => {
  port.write('ET');
  console.log("Iniciando Striming");
})

obs.on('StreamStopped', dato => {
  port.write('EF');
  console.log("Apagando Striming");
})
