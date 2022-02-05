/*
 *  This sketch demonstrates testing of BLE functionality
 *  Based existing GPIO functionality
 */

/* Arduino IDE will only compile libraries it knows are being used in the *.ino file
 * Hence if a library isn't listed here it will not be compiled 
 * Because I'm using libraries in other libraries I'm just listing them here 
 * until I find a better way. Even if they are not used here necessarily
 */
#include "Task_Measure.h"
#include "PS_FFat.h"
#include "config.h"

#define uS_TO_S_FACTOR 1000000ULL  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  5        /* Time ESP32 will go to sleep (in seconds) */

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
            break;
        case ESP_SLEEP_WAKEUP_EXT1:
            Serial.println("Wakeup caused by external signal using RTC_CNTL"); 
            break;
        case ESP_SLEEP_WAKEUP_TIMER: 
            Serial.println("Wakeup caused by timer");
            TaskMeasure::wakeInit();
            TaskMeasure::run();
            sleep();
            break;
        case ESP_SLEEP_WAKEUP_TOUCHPAD: 
            Serial.println("Wakeup caused by touchpad"); 
            break;
        case ESP_SLEEP_WAKEUP_ULP: 
            Serial.println("Wakeup caused by ULP program");
            break;
        default: 
            Serial.printf("Wakeup was not caused by deep sleep: %d\r\n",wakeup_reason); 
            TaskMeasure::fullInit();
            TaskMeasure::run();
            sleep();
            break;
    }
}

void loop()
{
    ;
}

void sleep(){
    esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
    Serial.println("Setup ESP32 to sleep for every " + String(TIME_TO_SLEEP) +
    " Seconds");
    Serial.flush(); 
    esp_deep_sleep_start();
}

