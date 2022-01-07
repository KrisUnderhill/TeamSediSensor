/* Task_Measure.cpp 
 * Turns on the LED and Phototransistor 
 * reads data off the adc pins
 */

#include "Arduino.h"
#include "Task_BLE.h"
#include "../Config/config.h" /* Include path for lib */

SimpleBLE TaskBLE::ble;
hw_timer_t * TaskBLE::timer = NULL;
volatile SemaphoreHandle_t TaskBLE::timerSemaphore = xSemaphoreCreateBinary();

void TaskBLE::init(){
    Serial.setDebugOutput(true);
    Serial.print("ESP32 SDK: ");
    Serial.println(ESP.getSdkVersion());
    ble.begin("ESP32 SimpleBLE");

    /* setup Timers - see timer example*/
    timer = timerBegin(1, 80, true); /* Timer # 0, 80 prescaler (us), count-up true */
    timerAttachInterrupt(timer, &TimerISR, true); /* attach ISR to interrupt */
    timerAlarmWrite(timer, 1000000, true); /* Timer fires every 15,000,000 us (15s), repeat true */
    timerAlarmEnable(timer); /* Enable timer alarms */
}

void TaskBLE::run(){
    if (xSemaphoreTake(timerSemaphore, 0) == pdTRUE){
        String out = "BLE32 name: ";
        out += String(millis() / 1000);
        Serial.println(out);
        ble.begin(out);
    }
}

void IRAM_ATTR TaskBLE::TimerISR(){
  // Give a semaphore that we can check in the loop
  xSemaphoreGiveFromISR(timerSemaphore, NULL);
}

