#include <WiFi.h>
#include <WebServer.h>
#include <HTTPClient.h>


//"http" is the object used to make http requests (Identification)
HTTPClient http;

// the Webserver wil receive http requests (i.e. orders)
WebServer server(80);


void WIFI_init(char* ssid, char* password, char* name) {

  //STarting the serial port :
  Serial.begin(115200);


  //Step 1 : Connecting to Wifi :

  Serial.print("connecting...");
  // Initiate wifi connection
  WiFi.begin(ssid, password);
  // Wait until connected :
  while (WiFi.status() != WL_CONNECTED ) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Wifi connected !" );

  // Step 2 : Presentation to Server :
  // The ESP32 decleres itself to serever, with its own IP :
  // Address of the server  + our IP :

  // Create the request :
  http.begin("http://192.168.1.112:5000/newbot/" + (WiFi.localIP().toString()) +"/"+ name);

  // execute the request with the GET method
  // and store the result in httpCode:
  int httpCode = http.GET();

  // If the code is positive, no error :
  if (httpCode > 0) {
    // store the message received in "playload"
    String payload = http.getString();
    Serial.println(httpCode);
    Serial.println(payload);
  }  else {
    Serial.println("Error on HTTP request");
  }



}
