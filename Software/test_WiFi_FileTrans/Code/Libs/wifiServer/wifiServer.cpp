#include "wifiServer.h"
 
WebServer wifiServer::server(80);
bool wifiServer::hasSD = false; 
 
void wifiServer::handleNotFound() {
  String dataFile = "/testFile.txt";
  String icon = "/favicon.ico";
  if(server.uri() == dataFile){
      loadDataFile();
      return;
  }
  if(server.uri() == icon){
      Serial.println("I requested the icon");
      loadIcon();
      return;
  }
  String message = "ERROR 404\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  server.send(404, "text/plain", message);
  Serial.print(message);
}

void wifiServer::loadDataFile(){
    String dataType = "application/octet-stream";
    File dataFile = SD.open("/testFile.txt"); 

    if (!dataFile) {
        return;
    }
  
    if (server.streamFile(dataFile, dataType) != dataFile.size()) {
      Serial.println("Sent less data than expected!");
    }
  
    dataFile.close();
}

void wifiServer::loadIcon(){
    String dataType = "image/x-icon";
    File dataFile = SD.open("/favicon.ico"); 

    if (!dataFile) {
        return;
    }
  
    if (server.streamFile(dataFile, dataType) != dataFile.size()) {
      Serial.println("Sent less data than expected!");
    }
  
    dataFile.close();
}

void wifiServer::handleGet() {
  String path = "/index.htm";
  String dataType = "text/html";
  File dataFile = SD.open(path.c_str());
  if (server.streamFile(dataFile, dataType) != dataFile.size()) {
    Serial.println("Sent less data than expected!");
  }
  dataFile.close();
}

void wifiServer::init(){
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.println(ssid);

  // Wait for connection
  uint8_t i = 0;
  while (WiFi.status() != WL_CONNECTED && i++ < 20) {//wait 10 seconds
    delay(500);
  }
  if (i == 21) {
    Serial.print("Could not connect to");
    //Serial.println(ssid);
    while (1) {
      delay(500);
    }
  }
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin(host)) {
    MDNS.addService("http", "tcp", 80);
    Serial.println("MDNS responder started");
    Serial.print("You can now connect to http://");
    Serial.print(host);
    Serial.println(".local");
  }

  server.on("/", HTTP_GET, handleGet);
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");

  if (SD.begin(SS)) {
    Serial.println("SD Card initialized.");
    hasSD = true;
  }
}

void wifiServer::run(){
  server.handleClient();
  delay(2);//allow the cpu to switch to other tasks
}

