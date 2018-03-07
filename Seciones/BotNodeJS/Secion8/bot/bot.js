console.log("iniciando bot");
// Descargar el modulo de twit
// npm install twit --save
var Twit = require('twit')

// Obtener los token en
// https://youtu.be/PnD51NT-whU
var T = new Twit({
  consumer_key: '',
  consumer_secret: '',
  access_token: '',
  access_token_secret: '',
  timeout_ms: 60 * 1000, // optional HTTP request timeout to apply to all requests.
})

var consulta = {
  q: '#alsw',
  count: 5
}

T.get('search/tweets', consulta, respuestas);

function respuestas(err, data, response) {
  var twuit = data.statuses;
  for (var i = 0; i < twuit.length; i++) {
    console.log(twuit[i].text);
  }
}
