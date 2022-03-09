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
#define LEDC_DUTY_ON            (1638) // Set duty to 20% 
#define LEDC_DUTY_OFF           (0) // Set duty to 0%.
#define LEDC_FREQUENCY          (1000) // Frequency in Hertz. Set frequency at 1 kHz

int TaskMeasure::activeReading = 0;
int TaskMeasure::darkReading = 0;
int TaskMeasure::tempAdc = 0;
char TaskMeasure::timeCStr[MSG_LEN] = {0};
bool TaskMeasure::readyToSleep = false;
int64_t TaskMeasure::nextRun = 0;
unsigned long TaskMeasure::lastStateChange = 0;
enum TaskMeasureStates TaskMeasure::taskMeasureState = WAITING;


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
    taskMeasureState = WAITING;

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
    taskMeasureState = WAITING;
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
    static struct tm tm;
    switch(taskMeasureState) {
        case WAITING: {
            if(getuSecs() > nextRun){
                nextRun += TIME_TO_SLEEP*uS_TO_S_FACTOR;
                digitalWrite(PHOTOTRANSISTOR_PIN, HIGH);
                lastStateChange = millis();
                taskMeasureState = AMB_MEASURE;
            } 
        } break; 
        case AMB_MEASURE: {
            if(millis() > lastStateChange + WAIT_PHOTOTRANSISTOR_ON_TO_AMB_MEASURE){
                darkReading = analogRead(ADC_PIN);
                lastStateChange = millis();
                taskMeasureState = LED_ON;
            }
        } break;
        case LED_ON: {
            if(millis() > lastStateChange + WAIT_AMB_MEASURE_TO_LED_ON){
                /* turn on LED */
                ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, LEDC_DUTY_ON);
                ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
                lastStateChange = millis();
                taskMeasureState = ACT_MEASURE;
            }
        } break;
        case ACT_MEASURE: {
            if(millis() > lastStateChange + WAIT_LED_ON_TO_ACT_MEASURE){
                /* take reading */
                activeReading = analogRead(ADC_PIN);
                /* Take time */        
                time_t t = time(NULL);
                tm = *localtime(&t);

                /* Take Temp */
                tempAdc = analogRead(TEMP_PIN);

                lastStateChange = millis();
                taskMeasureState = LED_OFF;
            }
        } break;
        case LED_OFF: {
            if(millis() > lastStateChange + WAIT_ACT_MEASURE_TO_LED_OFF){
                /* turn on LED */
                ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, LEDC_DUTY_OFF);
                ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
                lastStateChange = millis();
                taskMeasureState = COMPUTE_MEASURE;
            }
        } break;
        case COMPUTE_MEASURE: {
            /* Format string */
            sprintf(timeCStr, "%d-%02d-%02d %02d:%02d:%02d, %d, %.3f, %d, %.3f, %d, %.1f\n", 
                    tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, 
                    tm.tm_hour, tm.tm_min, tm.tm_sec, 
                    darkReading, getVoltageFromAdc(darkReading), 
                    activeReading, getVoltageFromAdc(activeReading),
                    tempAdc, getTempFromAdc(tempAdc));
            Serial.printf("%s\r", timeCStr);
            File f;
            if(PS_FileSystem::open(&f, DATA, FILE_APPEND)){
                f.write((const uint8_t*)timeCStr, strlen(timeCStr));
                PS_FileSystem::close(DATA);
            }
            readyToSleep = true;

            lastStateChange = millis();
            taskMeasureState = WAITING;
        } break;
        default:
            break;
    }
}

double TaskMeasure::getVoltageFromAdc(int adcReading){
    double voltage = ((double)adcReading/(double)MAX_ADC_READING)*MAX_VOLTAGE;
    return voltage;
}

double TaskMeasure::getTempFromAdc(int adcReading){
    double temp = getVoltageFromAdc(adcReading)/VOLTS_PER_DEG;
    return temp;
}

