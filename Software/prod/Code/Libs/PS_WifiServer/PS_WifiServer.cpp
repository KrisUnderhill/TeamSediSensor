#include "PS_WifiServer.h"
 
WebServer wifiServer::server(80);
HTTPUpdateServer wifiServer::httpUpdater;

void wifiServer::handleNotFound() {
    Serial.println("GOT FILE Request");
    String dataFile = "/data.csv";
    String icon = "/favicon.ico";
    if(server.uri() == dataFile){
        loadDataFile();
        return;
    }
    if(server.uri() == icon){
        loadIcon();
        return;
    }
#ifdef DEMO_ENABLED
    String demoChart = "/demo/chart.js";
    String demoMoment = "/demo/moment.js";
    String demoChartPlugin = "/demo/chartjs_plugin_annotation_min.js";
    String demoChartAdapter = "/demo/chartjs_adapter_moment";
    if(server.uri() == demoChart){
        File demoChartFile;
        PS_FileSystem::forceOpen(&demoChartFile, "/demo/chart.js", FILE_READ);
        if (server.streamFile(demoChartFile, "application/javascript" ) != demoChartFile.size()) {
            Serial.println("Sent less data than expected!");
        }
        return;
    }
    if(server.uri() == demoMoment) {
        File demoMomentFile;
        PS_FileSystem::forceOpen(&demoMomentFile, "/demo/moment.js", FILE_READ);
        if (server.streamFile(demoMomentFile, "application/javascript" ) != demoMomentFile.size()) {
            Serial.println("Sent less data than expected!");
        }
        return;
    }
    if(server.uri() == demoChartPlugin){
        File demoChartPluginFile;
        PS_FileSystem::forceOpen(&demoChartPluginFile, "/demo/chartjs_plugin_annotation_min.js", FILE_READ);
        if (server.streamFile(demoChartPluginFile, "application/javascript" ) != demoChartPluginFile.size()) {
            Serial.println("Sent less data than expected!");
        }
        return;
    }
    if(server.uri() == demoChartAdapter){
        File demoChartAdapterFile;
        PS_FileSystem::forceOpen(&demoChartAdapterFile, "/demo/charjs_adapter_moment", FILE_READ);
        if (server.streamFile(demoChartAdapterFile, "application/javascript" ) != demoChartAdapterFile.size()) {
            Serial.println("Sent less data than expected!");
        }
        return;
    }
#endif
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
    File dataFile; 
    if(!PS_FileSystem::open(&dataFile, DATA, FILE_READ)){
        Serial.println("Could not open file");
        return;
    }
  
    if (server.streamFile(dataFile, dataType) != dataFile.size()) {
      Serial.println("Sent less data than expected!");
    }

    PS_FileSystem::close(DATA);
}

void wifiServer::loadIcon(){
    String iconType = "image/x-icon";
    File iconFile; 

    if (!PS_FileSystem::open(&iconFile, ICON, FILE_READ)) {
        Serial.println("Could not return file");
        return;
    }
  
    if (server.streamFile(iconFile, iconType) != iconFile.size()) {
      Serial.println("Sent less data than expected!");
    }
  
    PS_FileSystem::close(ICON);
}

void wifiServer::handleGet() {
    Serial.println("GOT FILE Request");
    String htmlType = "text/html";
    File htmlFile;

    if (!PS_FileSystem::open(&htmlFile, HOME, FILE_READ)){
        Serial.println("Could not return file");
        return;
    }
    if (server.streamFile(htmlFile, htmlType) != htmlFile.size()) {
      Serial.println("Sent less data than expected!");
    }

    PS_FileSystem::close(HOME);
}

#if GOD_MODE_ENABLED == true
void wifiServer::handleGodMode() {
    Serial.println("GOT FILE Request");
    String htmlType = "text/html";
    File htmlFile;

    if (!PS_FileSystem::open(&htmlFile, GOD_HOME, FILE_READ)){
        Serial.println("Could not return file");
        return;
    }
    if (server.streamFile(htmlFile, htmlType) != htmlFile.size()) {
      Serial.println("Sent less data than expected!");
    }

    PS_FileSystem::close(GOD_HOME);
}

void wifiServer::handleGetMeasure(){
    server.send(200, "text/plain", String(TaskMeasure::getMeasure()));
}
#endif

#if DEMO_ENABLED == true
void wifiServer::handleDemo(){
    Serial.println("GOT Demo Request");
    String demoType = "text/html";
    File demoFile;
    if(!PS_FileSystem::forceOpen(&demoFile, "/demo/index.htm", FILE_READ)){
        Serial.println("Could not return file");
        return;
    }
    if(server.streamFile(demoFile, demoType) != demoFile.size()) {
        Serial.println("Sent Less than expected");
    }

    PS_FileSystem::forceClose("/demo/index.htm");
}
#endif

void wifiServer::start(){
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
    server.on("/measure.txt", HTTP_GET, handleGetMeasure);
#if GOD_MODE_ENABLED == true
    server.on("/god/", HTTP_GET, handleGodMode);
    httpUpdater.setup(&server, "/god/update/");
#endif
#if DEMO_ENABLED == true
    server.on("/demo", HTTP_GET, handleDemo);
#endif
    server.onNotFound(handleNotFound);

    server.begin();
    Serial.println("HTTP server started");
}

void wifiServer::run(){
    server.handleClient();
    delay(2);//allow the cpu to switch to other tasks
}

void wifiServer::stop(){
    server.stop();
    WiFi.enableAP(false);
}

