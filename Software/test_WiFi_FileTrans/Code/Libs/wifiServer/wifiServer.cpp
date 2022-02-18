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
  Serial.println("Configuring access point...");

  // You can remove the password parameter if you want the AP to be open.
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();

  Serial.println("Server started");

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

