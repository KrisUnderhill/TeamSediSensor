/* Task_Measure.cpp 
 * Turns on the LED and Phototransistor 
 * reads data off the adc pins
 */

#include "Arduino.h"
#include "Task_Measure.h"
#include "sys/time.h"
#include "stdio.h"
#include <time.h>
#include "../Config/config.h" /* Include path for lib */

int TaskMeasure::potReading = 0;
hw_timer_t * TaskMeasure::timer = NULL;
volatile SemaphoreHandle_t TaskMeasure::timerSemaphore = xSemaphoreCreateBinary();

void TaskMeasure::init(){
    /* setup pins */
    pinMode(LED_PIN, OUTPUT);
    /* Time setup - hacked from SimpleTime example and idf docs*/
    setenv("TZ", "EST+5EDT,M3.2.0/2,M11.1.0/2", 1); /* hardcoded eastern */
    tzset();
    struct timeval tv;
    tv.tv_sec = TIME_SEC;
    tv.tv_usec = TIME_USEC;
    settimeofday(&tv, NULL);

    /* setup Timers - see timer example*/
    timer = timerBegin(0, 80, true); /* Timer # 0, 80000 prescaler (us), count-up true */
    timerAttachInterrupt(timer, &TimerISR, true); /* attach ISR to interrupt */
    timerAlarmWrite(timer, 15000000, true); /* Timer fires every 15,000,000 us (15s), repeat true */
    timerAlarmEnable(timer); /* Enable timer alarms */
}

void TaskMeasure::run(){
    if (xSemaphoreTake(timerSemaphore, 0) == pdTRUE){
        //turn on LED
        digitalWrite(LED_PIN, HIGH);
        potReading = analogRead(POT_PIN);
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        Serial.printf("now: %d-%02d-%02d %02d:%02d:%02d\r\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
        Serial.println(potReading);
        // Wait 
        delay(1000);
        //turn off
        digitalWrite(LED_PIN, LOW);
    }
}

void IRAM_ATTR TaskMeasure::TimerISR(){
  // Give a semaphore that we can check in the loop
  xSemaphoreGiveFromISR(timerSemaphore, NULL);
}

/*

void loop() {
  // If Timer has fired
  if (xSemaphoreTake(timerSemaphore, 0) == pdTRUE){
    uint32_t isrCount = 0, isrTime = 0;
    // Read the interrupt count and time
    portENTER_CRITICAL(&timerMux);
    isrCount = isrCounter;
    isrTime = lastIsrAt;
    portEXIT_CRITICAL(&timerMux);

*/

