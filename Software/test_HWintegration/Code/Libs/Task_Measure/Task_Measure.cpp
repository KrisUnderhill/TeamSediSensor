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


void TaskMeasure::init(){
    pinMode(LED_PIN, OUTPUT);
    Serial.println("Setup done");
    setenv("TZ", "EST+5EDT,M3.2.0/2,M11.1.0/2", 1);
    tzset();
    struct timeval tv;
    tv.tv_sec = TIME_SEC;
    tv.tv_usec = TIME_USEC;
    settimeofday(&tv, NULL);
}

void TaskMeasure::run(){
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
    // wait
    delay(1000);
}

