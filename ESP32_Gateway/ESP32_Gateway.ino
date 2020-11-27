#include "lib_btle.h"
#include "lib_webserver.h"

// Wifi credentials for the local network
char* ssid = "ssid";  // Enter your SSID here
char* password = "password";  //Enter your Password here
char* name = "robotName" // Name of the robot (will be displayed on the webserver !)

void setup() {
  BTLE_init();
  WIFI_init(ssid, password);
  
  // If the ESP32 receive a request ended with "/go" :
  server.on("/go", handle_go);
  // If the ESP32 receive a request ended with "/stop" :
  server.on("/stop", handle_stop);
}

void loop() {
  // Manage BT events.
  bt_loop();
}


void handle_go() {
  // Send an "f" over BtLE 
  send_data("f");
}

void handle_stop() {
  // Send an "X" over BtLE 
  send_data("X");
}
