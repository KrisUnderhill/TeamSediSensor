/* Task_Measure.cpp 
 * Turns on the LED and Phototransistor 
 * reads data off the adc pins
 */

#include "Task_Measure.h"

#include "Arduino.h"
#include "sys/time.h"
#include "stdio.h"
#include <time.h>
#include "../Config/config.h" /* Include path for lib */
/* #include timer stuff - done automatically by Arduino IDE */

int TaskMeasure::activeReading = 0;
int TaskMeasure::darkReading = 0;
char TaskMeasure::timeCStr[BLE_MSG_LEN] = {0};

void TaskMeasure::fullInit(){
    /* init file system here */
    PS_FFat::fullInit();

    /* setup pins */
    pinMode(LED_PIN, OUTPUT);
    /* Time setup - hacked from SimpleTime example and idf docs*/
    setenv("TZ", TIME_ZONE, 1); /* hardcoded eastern */
    tzset();
    struct timeval tv;
    tv.tv_sec = TIME_SEC;
    tv.tv_usec = TIME_USEC;
    settimeofday(&tv, NULL);
}

void TaskMeasure::wakeInit(){
    setenv("TZ", TIME_ZONE, 1); /* hardcoded eastern */
    PS_FFat::wakeInit();
}

void TaskMeasure::run(){
    /* Read Dark Current */
    darkReading = analogRead(POT_PIN);

    /* turn on LED */
    digitalWrite(LED_PIN, HIGH);
    /* wait 0.5 sec */
    delay(500);
    /* take reading */
    activeReading = analogRead(POT_PIN);
    Serial.println(activeReading);
    /* Take time */        /* lol I already forgot how these time functions work */
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    /* Wait 0.5 sec */
    delay(500);
    /* turn LED off */
    digitalWrite(LED_PIN, LOW);

    /* Format string */
    sprintf(timeCStr, "%d-%02d-%02d %02d:%02d:%02d, %d, %.3f, %d, %.3f\n", 
            tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, 
            tm.tm_hour, tm.tm_min, tm.tm_sec, 
            darkReading, getVoltageFromAdc(darkReading), activeReading, getVoltageFromAdc(activeReading));
    Serial.printf("%s\r", timeCStr);
    //taskB.setBuffer((uint8_t*)timeCStr, strlen(timeCStr)-1); /* -1 : I don't want the \n char or the \0 end */
    PS_FFat::setBuffer(timeCStr, strlen(timeCStr)+1); /* +1: I do want the \n and the \0 chars */
}

float TaskMeasure::getVoltageFromAdc(int adcReading){
    float voltage = ((float)adcReading/(float)MAX_ADC)*MAX_VOLT;
    return voltage;
}

