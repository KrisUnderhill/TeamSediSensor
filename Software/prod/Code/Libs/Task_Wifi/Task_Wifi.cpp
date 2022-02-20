/*
 * Based on arduino for ESP32 examples
 *   SDWebServer
 *   AP
 *   Modified to fit TSS Senior design project Kris Miedema
 */

#include "Task_Wifi.h"

volatile bool TaskWifi::startWifi = false;
volatile bool TaskWifi::runningWifi = false;
volatile bool TaskWifi::stopWifi = false;
volatile bool TaskWifi::taskRunning = true;
esp_timer_handle_t TaskWifi::shutOffTimer;
esp_timer_create_args_t TaskWifi::shutOffTimerArgs = {
    .callback = &shutOffTimerCallback,
};


void IRAM_ATTR TaskWifi::buttonInt(){
    startWifi = true;
}

void TaskWifi::init(){
    /* Add intr to start Wifi Server */
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    attachInterrupt(BUTTON_PIN, buttonInt, FALLING);
    esp_timer_create(&shutOffTimerArgs, &shutOffTimer);
}

void TaskWifi::run(){
    if(taskRunning) {
        if(startWifi) {
            startWifi = false;
            runningWifi = true;
            startServer();
            esp_timer_start_periodic(shutOffTimer, 30*1000000);
            TaskMeasure::pauseTask();
        }
        if(runningWifi){
            wifiServer::run();
            static unsigned long last_millis = millis();
            if((millis()-last_millis) > 5000) {
                Serial.printf("Number Connected is: %d\r\n", wifiServer::getNumConnected());
                last_millis = millis();
            }
        }
        if(stopWifi) {
            runningWifi = false;
            stopWifi = false;
            TaskWifi::stopServer();
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

void TaskWifi::shutOffTimerCallback(void* args){
    (void) args;
    if(wifiServer::getNumConnected() == 0) {
        stopWifi = true;
    }
}
