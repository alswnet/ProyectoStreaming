console.log("iniciando bot");

var Twit = require('twit')

var T = new Twit({
  consumer_key:         '',
  consumer_secret:      '',
  access_token:         '',
  access_token_secret:  '',
  timeout_ms:           60*1000,  // optional HTTP request timeout to apply to all requests.
})

var publicasion ={
  status: "hola este es un bot en nodejs #ALSW"
}

T.post('statuses/update',publicasion,CallPublicar);

function CallPublicar(err, data, response){
  if(err){
    console.log("Fallo algo");
  }
  else{
    console.log("Exito");
  }
}
