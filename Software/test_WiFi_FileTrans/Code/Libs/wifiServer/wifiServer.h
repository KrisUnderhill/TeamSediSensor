#ifndef _WIFI_SERVER_H_
#define _WIFI_SERVER_H_

#include "Arduino.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <SPI.h>
#include <SD.h>

class wifiServer {
    public:
        static void init();
        static void run();

    private:
        static void returnOK();
        static void returnFail(String msg);
        static bool loadFromSdCard(String path);
        static void handleFileUpload();
        static void deleteRecursive(String path);
        static void handleDelete();
        static void handleCreate();
        static void printDirectory();
        static void handleNotFound();

        /* This is against iso c but char id[] doesn't work
         * idk why I get linker errors 
         * since this is only a temp method 
         * until an ap is running imma leave it 
         */
        static constexpr char* ssid = "Kenneth";
        static constexpr char* password = "keineahnung";
        static constexpr char* host = "esp32sd";

        static WebServer server;

        static bool hasSD;
        static File uploadFile;
};

#endif /*_WIFI_SERVER_H_*/
