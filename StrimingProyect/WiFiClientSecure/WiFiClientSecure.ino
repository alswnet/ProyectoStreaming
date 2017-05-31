
// "https://graph.facebook.com/v2.9/me?fields=id%2Cname&access_token=xxxx"

#include <WiFiClientSecure.h>

const char* ssid     = "TURBONETT_ALSW";     // your network SSID (name of wifi network)
const char* password = "2526-4897"; // your network password

const char*  server = "facebook.com";  // Server URL

WiFiClientSecure client;

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  delay(100);

  Serial.print("Attempting to connect to SSID: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  // attempt to connect to Wifi network:
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    // wait 1 second for re-trying
    delay(1000);
  }

  Serial.print("Connected to ");
  Serial.println(ssid);
  
 
  Serial.println("\nStarting connection to server...");
  if (!client.connect(server, 443))
	  Serial.println("Connection failed!");
  else {
    Serial.println("Connected to server!");
    // Make a HTTP request:
    client.println("GET https://graph.facebook.com/v2.9/alswnet?access_token=EAACEdEose0cBALWleg0SColyajYQbHWAvi2XXOEU4CFx2dcCq02ZCSfzWnDKiIMnwjtVzGmHOJTvZB0mRXN6KYmSNv3I40ydAUVc3YPWZCcZCnuqNJGDStbAl5FlbvQ0BMNgDhXkPt2VdUQpMR3j6dIt9lzF9y1xlF7HjaPdfurZBtXJrV0Dn HTTP/1.0");
    client.println("Host: www.graph.facebook.com");
    client.println("Connection: close");
    client.println();

	Serial.print("Waiting for response "); //WiFiClientSecure uses a non blocking implementation
	while (!client.available()){
		delay(50); //
		Serial.print(".");
	}	 
    // if there are incoming bytes available
    // from the server, read them and print them:
    while (client.available()) {
      char c = client.read();
      Serial.write(c);
    }

    // if the server's disconnected, stop the client:
    if (!client.connected()) {
      Serial.println();
      Serial.println("disconnecting from server.");
      client.stop();
    }
  }
}

void loop() {
  // do nothing
}
