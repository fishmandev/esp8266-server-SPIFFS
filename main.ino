// Load Wi-Fi library
#include <ESP8266WiFi.h>
#include "ESP8266WebServer.h"
#include <FS.h>   // Include the SPIFFS library

// Set web server port number to 80
ESP8266WebServer server(80);

void handleRootPath() {
  String path = "/index.html";
  if (SPIFFS.exists(path)) {
    File file = SPIFFS.open(path, "r");
    size_t sent = server.streamFile(file, "text/html");
    file.close();
  } else {
    server.send(404, "text/plain", "404: Not Found");
  }
}

void setup() {
  SPIFFS.begin();
  server.on("/", handleRootPath);
  server.begin();
}

void loop() {
  server.handleClient(); //Handling of incoming requests  
}
