/*
 * Based on arduino for ESP32 examples
 *   SDWebServer
 *   AP
 *   Modified to fit TSS Senior design project Kris Miedema
 */

#include "Task_Wifi.h"

bool TaskWifi::readyToSleep = true;
enum TaskWifiStates TaskWifi::taskWifiState = TASK_WIFI_OFF;
esp_timer_handle_t TaskWifi::shutOffTimer;
esp_timer_create_args_t TaskWifi::shutOffTimerArgs = {
    .callback = &shutOffTimerCallback,
};


void IRAM_ATTR TaskWifi::buttonInt(){
    if(taskWifiState == TASK_WIFI_OFF)
        taskWifiState = TASK_WIFI_START;
}

void TaskWifi::fullInit(){
    /* Add intr to start Wifi Server */
    pinMode(BUTTON_PIN, INPUT_PULLDOWN);
    attachInterrupt(BUTTON_PIN, buttonInt, RISING);
    esp_timer_create(&shutOffTimerArgs, &shutOffTimer);
    if(WIFI_ALWAYS_ON){
        taskWifiState = TASK_WIFI_START;
    }
}

void TaskWifi::wakeInit(){
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    attachInterrupt(BUTTON_PIN, buttonInt, FALLING);
    esp_timer_create(&shutOffTimerArgs, &shutOffTimer);
    if(WIFI_ALWAYS_ON){
        taskWifiState = TASK_WIFI_START;
    }
}

void TaskWifi::run(){
    switch(taskWifiState){
        case TASK_WIFI_OFF:
            break;
        case TASK_WIFI_START:
            readyToSleep = false;
            startServer();
            esp_timer_start_periodic(shutOffTimer, 30*1000000);

            taskWifiState = TASK_WIFI_RUN;
            break;
        case TASK_WIFI_RUN:
            wifiServer::run();
            static unsigned long last_millis = millis();
            if((millis()-last_millis) > 5000) {
                Serial.printf("Number Connected is: %d\r\n", wifiServer::getNumConnected());
                last_millis = millis();
            }
            break;
        case TASK_WIFI_STOP:
            TaskWifi::stopServer();
            readyToSleep = true;

            taskWifiState = TASK_WIFI_OFF;
            break;
        default:
            break;
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
            taskWifiState = TASK_WIFI_STOP;
    }
}
