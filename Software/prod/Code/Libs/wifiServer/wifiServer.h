#ifndef _WIFI_SERVER_H_
#define _WIFI_SERVER_H_

#include "Arduino.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <SPI.h>
#include <SD.h>

class wifiServer {
    public:
        static void start();
        static void stop();
        static void run();
    private:
        static void handleNotFound();
        static void handleGet();
        static void loadDataFile();
        static void loadIcon();

        /* This is against iso c but char id[] doesn't work
         * idk why I get linker errors 
         * since this is only a temp method 
         * until an ap is running imma leave it 
         */
        static constexpr char* ssid = "TSS";
        static constexpr char* password = "teamsedisensor";
        static constexpr char* host = "TSS";

        static WebServer server;

        static bool hasSD;
        static File uploadFile;
};

#endif /*_WIFI_SERVER_H_*/
