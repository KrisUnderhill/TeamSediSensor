/* Task_Measure.cpp 
 * Turns on the LED and Phototransistor 
 * reads data off the adc pins
 */

#include "Arduino.h"
#include "Task_Measure.h"

#include "driver/ledc.h" /* ~/.arduino15/packages/esp32/hardware/esp32/1.0.6/tools/sdk/include/driver/driver */
#include "sys/time.h"
#include "stdio.h"
#include <time.h>

#include "../Config/config.h" /* Include path for lib */
#include "../PS_FileSystem/PS_FileSystem.h"
/* #include timer stuff - done automatically by Arduino IDE */

#define LEDC_TIMER              LEDC_TIMER_1
#define LEDC_MODE               LEDC_LOW_SPEED_MODE
#define LEDC_OUTPUT_IO          LED_PIN
#define LEDC_CHANNEL            LEDC_CHANNEL_0
#define LEDC_DUTY_RES           LEDC_TIMER_13_BIT // Set duty resolution to 13 bits
#define LEDC_DUTY_ON            (8192) // Set duty to 100% 
#define LEDC_DUTY_OFF           (0) // Set duty to 0%.
#define LEDC_FREQUENCY          (5000) // Frequency in Hertz. Set frequency at 5 kHz

volatile bool TaskMeasure::taskRunning = true;
int TaskMeasure::activeReading = 0;
int TaskMeasure::darkReading = 0;
int TaskMeasure::tempAdc = 0;
char TaskMeasure::timeCStr[MSG_LEN] = {0};
bool TaskMeasure::readyToSleep = false;
int64_t TaskMeasure::nextRun = 0;

void TaskMeasure::fullInit(){
    /* init file system here */
    PS_FileSystem::fullInit();

    /* setup pins */
    pinMode(PHOTOTRANSISTOR_PIN, OUTPUT);

    /* Time setup - hacked from SimpleTime example and idf docs*/
    setenv("TZ", TIME_ZONE, 1); /* hardcoded eastern */
    tzset();
    struct timeval tv;
    tv.tv_sec = TIME_SEC;
    tv.tv_usec = TIME_USEC;
    settimeofday(&tv, NULL);

    nextRun = getuSecs() + TIME_TO_SLEEP*uS_TO_S_FACTOR;

    /* setup LEDC to control LED */
    ledc_timer_config_t ledc_timer = {
        LEDC_MODE,
        LEDC_DUTY_RES,
        LEDC_TIMER,
        LEDC_FREQUENCY,  // Set output frequency at 5 kHz
    };

    ledc_timer_config(&ledc_timer);

    // Prepare and then apply the LEDC PWM channel configuration
    ledc_channel_config_t ledc_channel = {
        .gpio_num       = LEDC_OUTPUT_IO,
        .speed_mode     = LEDC_MODE,
        .channel        = LEDC_CHANNEL,
        .intr_type      = LEDC_INTR_DISABLE,
        .timer_sel      = LEDC_TIMER,
        .duty           = 0, // Set duty to 0%
        .hpoint         = 0
    };

    ledc_channel_config(&ledc_channel);
}

void TaskMeasure::wakeInit(){
    PS_FileSystem::wakeInit();

    pinMode(PHOTOTRANSISTOR_PIN, OUTPUT);

    /* reset timezone to eastern, not preserved through reset */
    setenv("TZ", TIME_ZONE, 1); /* hardcoded eastern */

    /* setup LEDC to control LED */
    ledc_timer_config_t ledc_timer = {
        LEDC_MODE,
        LEDC_DUTY_RES,
        LEDC_TIMER,
        LEDC_FREQUENCY,  // Set output frequency at 5 kHz
    };

    ledc_timer_config(&ledc_timer);

    // Prepare and then apply the LEDC PWM channel configuration
    ledc_channel_config_t ledc_channel = {
        .gpio_num       = LEDC_OUTPUT_IO,
        .speed_mode     = LEDC_MODE,
        .channel        = LEDC_CHANNEL,
        .intr_type      = LEDC_INTR_DISABLE,
        .timer_sel      = LEDC_TIMER,
        .duty           = 0, // Set duty to 0%
        .hpoint         = 0
    };

    ledc_channel_config(&ledc_channel);

}

int64_t TaskMeasure::getuSecs(){
    struct timeval tv_now;
    gettimeofday(&tv_now, NULL);
    int64_t time_us = ((int64_t)tv_now.tv_sec * uS_TO_S_FACTOR + (int64_t)tv_now.tv_usec);
    //Serial.println(time_us);
    return time_us;
}

void TaskMeasure::run(){
    if(taskRunning) {
        if(getuSecs() > nextRun){
            nextRun += TIME_TO_SLEEP*uS_TO_S_FACTOR;
            digitalWrite(PHOTOTRANSISTOR_PIN, HIGH);
            delay(2000);
            /* Read Dark Current */
            darkReading = analogRead(ADC_PIN);

            /* turn on LED */
            ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, LEDC_DUTY_ON);
            ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
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
            ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, LEDC_DUTY_OFF);
            ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);

            tempAdc = analogRead(TEMP_PIN);

            /* Format string */
            sprintf(timeCStr, "%d-%02d-%02d %02d:%02d:%02d, %d, %.3f, %d, %.3f, %d, %.1f\n", 
                    tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, 
                    tm.tm_hour, tm.tm_min, tm.tm_sec, 
                    darkReading, getVoltageFromAdc(darkReading), 
                    activeReading, getVoltageFromAdc(activeReading),
                    tempAdc, getTempFromAdc(tempAdc));
            Serial.printf("%s\r", timeCStr);
            File f;
            PS_FileSystem::open(&f, DATA, FILE_APPEND);
            f.write((const uint8_t*)timeCStr, strlen(timeCStr));
            PS_FileSystem::close(DATA);
            readyToSleep = true;
        }
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

