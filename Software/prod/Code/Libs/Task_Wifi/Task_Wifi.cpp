/*
 * Based on arduino for ESP32 examples
 *   SDWebServer
 *   AP
 *   Modified to fit TSS Senior design project Kris Miedema
 */

#include "Task_Wifi.h"

volatile bool TaskWifi::startWifi = false;
volatile bool TaskWifi::runningWifi = false;
volatile bool TaskWifi::taskRunning = true;

void IRAM_ATTR TaskWifi::buttonInt(){
    startWifi = true;
}

void TaskWifi::init(){
    /* Add intr to start Wifi Server */
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    attachInterrupt(BUTTON_PIN, buttonInt, FALLING);
}

void TaskWifi::run(){
    if(taskRunning) {
        if(startWifi) {
            startWifi = false;
            runningWifi = true;
            startServer();
            TaskMeasure::pauseTask();
        }
        if(runningWifi){
            wifiServer::run();
        }
    }
}

void TaskWifi::startServer(){
    wifiServer::start();
}

void TaskWifi::stopServer(){
    wifiServer::stop();
    TaskMeasure::resumeTask();
}


