#ifndef _WIFI_SERVER_H_
#define _WIFI_SERVER_H_

#include "Arduino.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <WebServer.h>
#include <ESPmDNS.h>

#include "../PS_FileSystem/PS_FileSystem.h"

#define ssid "TSS"
#define password "teamsedisensor"
#define host "TSS"

class wifiServer {
    public:
        static void start();
        static void stop();
        static void run();
        static uint8_t getNumConnected() { return WiFi.softAPgetStationNum(); }
    private:
        static void handleNotFound();
        static void handleGet();
        static void loadDataFile();
        static void loadIcon();

        static WebServer server;
};

#endif /*_WIFI_SERVER_H_*/
