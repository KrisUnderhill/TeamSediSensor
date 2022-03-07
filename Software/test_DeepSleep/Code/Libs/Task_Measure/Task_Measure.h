#ifndef TASK_MEASURE_H_
#define TASK_MEASURE_H_

#include "Arduino.h"
#include <time.h>
#include "../PS_FFat/PS_FFat.h"

#define POT_PIN 34
#define LED_PIN 22
#define MAX_VOLT 3.3
#define MAX_ADC 4095
#define BLE_MSG_LEN 500
#define TIME_ZONE "EST+5EDT,M3.2.0/2,M11.1.0/2"

class TaskMeasure {
    public: 
        static void fullInit();
        static void wakeInit();
        static void run();
    private:
        static float getVoltageFromAdc(int adcReading);
        static int darkReading;
        static int activeReading;
        static hw_timer_t * timer;
        static volatile SemaphoreHandle_t timerSemaphore;
        static char timeCStr[BLE_MSG_LEN];
};

#endif /* TASK_MEASURE_H_ */

