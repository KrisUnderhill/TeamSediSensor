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
#include "../PS_SDFile/PS_SDFile.h"
/* #include timer stuff - done automatically by Arduino IDE */

int TaskMeasure::activeReading = 0;
int TaskMeasure::darkReading = 0;
int TaskMeasure::tempAdc = 0;
hw_timer_t * TaskMeasure::timer = NULL;
volatile SemaphoreHandle_t TaskMeasure::timerSemaphore = xSemaphoreCreateBinary();
char TaskMeasure::timeCStr[BLE_MSG_LEN] = {0};

void TaskMeasure::init(){
    /* init file system here */
    PS_SDFile::init();

    /* setup pins */
    pinMode(LED_PIN, OUTPUT);
    pinMode(PHOTOTRANSISTOR_PIN, OUTPUT);
    /* Time setup - hacked from SimpleTime example and idf docs*/
    setenv("TZ", "EST+5EDT,M3.2.0/2,M11.1.0/2", 1); /* hardcoded eastern */
    tzset();
    struct timeval tv;
    tv.tv_sec = TIME_SEC;
    tv.tv_usec = TIME_USEC;
    settimeofday(&tv, NULL);

    /* setup Timers - see timer example*/
    timer = timerBegin(0, 80, true); /* Timer # 0, 80 prescaler (us), count-up true */
    timerAttachInterrupt(timer, &TimerISR, true); /* attach ISR to interrupt */
    timerAlarmWrite(timer, 5000000, true); /* Timer fires every 5,000,000 us (5s), repeat true */
    timerAlarmEnable(timer); /* Enable timer alarms */
}

void TaskMeasure::run(){
    if (xSemaphoreTake(timerSemaphore, 0) == pdTRUE){
        digitalWrite(PHOTOTRANSISTOR_PIN, HIGH);
        delay(2000);
        /* Read Dark Current */
        darkReading = analogRead(ADC_PIN);

        /* turn on LED */
        digitalWrite(LED_PIN, HIGH);
        /* wait 0.5 sec */
        delay(1500);
        /* take reading */
        activeReading = analogRead(ADC_PIN);
        /* Take time */        
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        /* Wait 0.5 sec */
        delay(500);
        /* turn LED off */
        digitalWrite(LED_PIN, LOW);
        tempAdc = analogRead(TEMP_PIN);

        /* Format string */
        sprintf(timeCStr, "%d-%02d-%02d %02d:%02d:%02d, %d, %.3f, %d, %.3f, %d, %.1f\n", 
                tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, 
                tm.tm_hour, tm.tm_min, tm.tm_sec, 
                darkReading, getVoltageFromAdc(darkReading), 
                activeReading, getVoltageFromAdc(activeReading),
                tempAdc, getTempFromAdc(tempAdc));
        Serial.printf("%s\r", timeCStr);
        //taskB.setBuffer((uint8_t*)timeCStr, strlen(timeCStr)-1); /* -1 : I don't want the \n char or the \0 end */
        PS_SDFile::setBuffer(timeCStr, strlen(timeCStr)+1); /* +1: I do want the \n and the \0 chars */
    }
}

double TaskMeasure::getVoltageFromAdc(int adcReading){
    double voltage = ((double)adcReading/(double)maxAdcReading)*maxVoltage;
    return voltage;
}

double TaskMeasure::getTempFromAdc(int adcReading){
    double temp = getVoltageFromAdc(adcReading)/VOLTS_PER_DEG;
    return temp;
}

void IRAM_ATTR TaskMeasure::TimerISR(){
  // Give a semaphore that we can check in the loop
  xSemaphoreGiveFromISR(timerSemaphore, NULL);
}
