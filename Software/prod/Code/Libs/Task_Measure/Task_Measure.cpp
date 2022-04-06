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
#define LEDC_FREQUENCY          (1000) // Frequency in Hertz. Set frequency at 1 kHz

std::vector<int> TaskMeasure::darkReading_v(NUM_TO_AVG);
std::vector<int> TaskMeasure::actReading_v(NUM_TO_AVG);
std::vector<int> TaskMeasure::tempAdc_v(NUM_TO_AVG);
std::vector<int> TaskMeasure::battAdc_v(NUM_TO_AVG);

char TaskMeasure::timeCStr[MSG_LEN] = {0};
bool TaskMeasure::readyToSleep = false;
int64_t TaskMeasure::nextRun = 0;
unsigned long TaskMeasure::lastStateChange = 0;
enum TaskMeasureStates TaskMeasure::taskMeasureState = WAITING;
int TaskMeasure::stateIndex = 0;


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
    readyToSleep = true;
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
                Serial.printf("State Waiting, time: %ld\n", millis());
                nextRun += TIME_TO_SLEEP*uS_TO_S_FACTOR;
                digitalWrite(PHOTOTRANSISTOR_PIN, HIGH);
                darkReading_v.clear();
                actReading_v.clear();
                tempAdc_v.clear();
                battAdc_v.clear();
                lastStateChange = millis();
                taskMeasureState = AMB_MEASURE;
                stateIndex = 0;
            } 
        } break; 
        case AMB_MEASURE: {
            if(millis() > lastStateChange + WAIT_PHOTOTRANSISTOR_ON_TO_AMB_MEASURE){
                Serial.printf("State amb Measure, time: %ld ", millis());
                int darkVal= analogRead(ADC_PIN);
                Serial.printf("adc: %d\n", darkVal);
                darkReading_v.push_back(darkVal);
                lastStateChange = millis();
                taskMeasureState = LED_ON;
            }
        } break;
        case LED_ON: {
            if(millis() > lastStateChange + WAIT_AMB_MEASURE_TO_LED_ON){
                Serial.printf("State led on, time: %ld\n", millis());
                /* turn on LED */
                ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, LEDC_DUTY_ON);
                ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
                lastStateChange = millis();
                taskMeasureState = ACT_MEASURE;
            }
        } break;
        case ACT_MEASURE: {
            if(millis() > lastStateChange + WAIT_LED_ON_TO_ACT_MEASURE){
                Serial.printf("State act measure, time: %ld ", millis());
                /* take reading */
                int activeVal = analogRead(ADC_PIN);
                Serial.printf("adc: %d\n", activeVal);
                actReading_v.push_back(activeVal);

                /* Take Temp */
                int tempAdcVal = analogRead(TEMP_PIN);
                tempAdc_v.push_back(tempAdcVal);
                
                /* Take Batt */
                int battAdcVal = analogRead(BATT_PIN);
                battAdc_v.push_back(battAdcVal);

                lastStateChange = millis();
                taskMeasureState = LED_OFF;
            }
        } break;
        case LED_OFF: {
            if(millis() > lastStateChange + WAIT_ACT_MEASURE_TO_LED_OFF){
                /* turn on LED */
                Serial.printf("State led off, time: %ld\n", millis());
                ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, LEDC_DUTY_OFF);
                ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
                lastStateChange = millis();
                if(stateIndex < NUM_TO_AVG){
                    stateIndex++;
                    taskMeasureState = AMB_MEASURE;
                } else{
                    taskMeasureState = COMPUTE_MEASURE;
                }
            }
        } break;
        case COMPUTE_MEASURE: {
            /* Take time */        
            time_t t = time(NULL);
            tm = *localtime(&t);

            int darkReadingAvg = 0, activeReadingAvg = 0, tempAdcAvg = 0, battAdcAvg = 0;
            for(int i = 0; i < NUM_TO_AVG; i++){
                darkReadingAvg += darkReading_v[i];
                activeReadingAvg += actReading_v[i];
                tempAdcAvg += tempAdc_v[i];
                battAdcAvg += battAdc_v[i];
            }
            darkReadingAvg /= NUM_TO_AVG;
            activeReadingAvg /= NUM_TO_AVG;
            tempAdcAvg /= NUM_TO_AVG;
            battAdcAvg /= NUM_TO_AVG;

            /* Format string -- CSV Format 
             * Timestamp, dark Reading, dark Reading V, active Reading, active Reading V, 
             * tempAdc, temp F, battAdc, batt V, diff, diff V*/
            snprintf(timeCStr, MSG_LEN, "%d-%02d-%02d %02d:%02d:%02d, %d, %.3f, %d, %.3f, %d, %.1f, %d, %.3f, %d, %.3f, %.3f", 
                    tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, 
                    tm.tm_hour, tm.tm_min, tm.tm_sec, 
                    darkReadingAvg, getVoltageFromAdc(darkReadingAvg), 
                    activeReadingAvg, getVoltageFromAdc(activeReadingAvg),
                    tempAdcAvg, getTempFromAdc(tempAdcAvg),
                    battAdcAvg, getVoltageFromAdc(battAdcAvg),
                    activeReadingAvg - darkReadingAvg, getVoltageFromAdc(activeReadingAvg - darkReadingAvg),
                    getNtuFromAdc(darkReadingAvg, activeReadingAvg));
            if(!validMeasure(darkReadingAvg, activeReadingAvg)){
                snprintf(timeCStr, MSG_LEN, "%s, *\n", timeCStr);
            } else{
                snprintf(timeCStr, MSG_LEN, "%s\n", timeCStr);
            }
            Serial.printf("%s\r", timeCStr);
            File f;
            if(PS_FileSystem::open(&f, DATA, FILE_APPEND)){
                f.write((const uint8_t*)timeCStr, strlen(timeCStr));
                PS_FileSystem::close(DATA);
            }

            lastStateChange = millis();
            taskMeasureState = WAITING;

            readyToSleep = true;
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

double TaskMeasure::getNtuFromAdc(int ambReading, int actReading){
    double readingDiff = (double)actReading - (double)ambReading;
    double ntuCalibrated = (readingDiff + 40.327)/(1.1755);
    return ntuCalibrated;
}

bool TaskMeasure::validMeasure(int ambReading, int actReading){
    const int LOWER_LIMIT_ADC = 76;
    const int SATURATION_LIMIT_ADC = 4000;
    if(ambReading > SATURATION_LIMIT_ADC)
        return false;
    if(actReading > SATURATION_LIMIT_ADC)
        return false;
    if((actReading - ambReading) < LOWER_LIMIT_ADC)
        return false;
    return true;
}
