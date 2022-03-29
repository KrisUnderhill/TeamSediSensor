#ifndef _WIFI_SERVER_H_
#define _WIFI_SERVER_H_

#include "Arduino.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <HTTPUpdateServer.h>

#include "../PS_FileSystem/PS_FileSystem.h"
#include "../Task_Measure/Task_Measure.h"

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
        static void handleGodMode();
        static void handleGetMeasure();
        static void loadDataFile();
        static void loadIcon();

        static WebServer server;
        static HTTPUpdateServer httpUpdater;
};

#endif /*_WIFI_SERVER_H_*/
