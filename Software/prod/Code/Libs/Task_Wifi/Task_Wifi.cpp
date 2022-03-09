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
bool TaskWifi::readyToSleep = true;
esp_timer_handle_t TaskWifi::shutOffTimer;
esp_timer_create_args_t TaskWifi::shutOffTimerArgs = {
    .callback = &shutOffTimerCallback,
};


void IRAM_ATTR TaskWifi::buttonInt(){
    startWifi = true;
}

void TaskWifi::fullInit(){
    /* Add intr to start Wifi Server */
    pinMode(BUTTON_PIN, INPUT_PULLDOWN);
    attachInterrupt(BUTTON_PIN, buttonInt, RISING);
    esp_timer_create(&shutOffTimerArgs, &shutOffTimer);
    if(WIFI_ALWAYS_ON){
        runningWifi = true;
        startServer();
    }
}

void TaskWifi::wakeInit(){
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    attachInterrupt(BUTTON_PIN, buttonInt, FALLING);
    esp_timer_create(&shutOffTimerArgs, &shutOffTimer);
    if(WIFI_ALWAYS_ON){
        runningWifi = true;
        startServer();
    }
}

void TaskWifi::run(){
    if(taskRunning) {
        if(!WIFI_ALWAYS_ON){
            if(startWifi) {
                startWifi = false;
                runningWifi = true;
                readyToSleep = false;
                startServer();
                esp_timer_start_periodic(shutOffTimer, 30*1000000);
            }
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
            TaskWifi::stopServer();
            runningWifi = false;
            stopWifi = false;
            readyToSleep = true;
        }
    }
}

void TaskWifi::startServer(){
    wifiServer::start();
}

void TaskWifi::stopServer(){
    wifiServer::stop();
    esp_timer_stop(shutOffTimer);
}

void TaskWifi::shutOffTimerCallback(void* args){
    (void) args;
    if(wifiServer::getNumConnected() == 0) {
        if(!WIFI_ALWAYS_ON)
            stopWifi = true;
    }
}
