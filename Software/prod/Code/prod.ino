/*
 *  This sketch is the production intent software
 *  Powers the Phototransistor + amplifier 
 *  Controls the LED
 *  reads data from the ADC
 */

/* Arduino IDE will only compile libraries it knows are being used in the *.ino file
 * Hence if a library isn't listed here it will not be compiled 
 * Because I'm using libraries in other libraries I'm just listing them here 
 * until I find a better way. Even if they are not used here necessarily
 */
#include "Task_Measure.h"
#include "PS_FileSystem.h"
#include "config.h"
#include "Task_Wifi.h"
#include "PS_WifiServer.h"

std::string inputString = "";
bool stringComplete = false;

void setup()
{    
    delay(1000);
    Serial.begin(115200);

    esp_sleep_wakeup_cause_t wakeup_reason;
    wakeup_reason = esp_sleep_get_wakeup_cause();

    switch(wakeup_reason)
    {
        case ESP_SLEEP_WAKEUP_EXT0: 
            Serial.println("Wakeup caused by external signal using RTC_IO"); 
            TaskMeasure::wakeInit();
            TaskWifi::wakeInit();
            TaskWifi::callIntr();
            break;
        case ESP_SLEEP_WAKEUP_EXT1:
            Serial.println("Wakeup caused by external signal using RTC_CNTL"); 
            break;
        case ESP_SLEEP_WAKEUP_TIMER: 
            Serial.println("Wakeup caused by timer");
            TaskMeasure::wakeInit();
            TaskWifi::wakeInit();
            break;
        case ESP_SLEEP_WAKEUP_TOUCHPAD: 
            Serial.println("Wakeup caused by touchpad"); 
            break;
        case ESP_SLEEP_WAKEUP_ULP: 
            Serial.println("Wakeup caused by ULP program");
            break;
        default: 
            Serial.printf("Wakeup was not caused by deep sleep: %d\r\n",wakeup_reason); 
            Serial.println("First wake up");
            TaskMeasure::fullInit();
            TaskWifi::fullInit();
            break;
    }
}

void loop()
{
    /* TODO debug TaskMeasure and Task_Wifi  message passing
     * especially semaphores to protect file access
     */
    TaskMeasure::run(); 
    TaskWifi::run();
    sleep();
}

void sleep(){
    if(TaskMeasure::getReadyToSleep() && TaskWifi::getReadyToSleep()){
        Serial.println("Setup ESP32 to sleep for every " + String(TIME_TO_SLEEP) +
        " Seconds");
        Serial.flush(); 
        esp_sleep_enable_ext0_wakeup((gpio_num_t)BUTTON_PIN, 1);
        esp_sleep_enable_timer_wakeup(TaskMeasure::getTimeToSleep());
        esp_deep_sleep_start();
    }
}

