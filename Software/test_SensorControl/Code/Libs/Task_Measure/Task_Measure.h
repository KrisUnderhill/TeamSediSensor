#ifndef TASK_MEASURE_H_
#define TASK_MEASURE_H_

#include "Arduino.h"
#include <time.h>
#include "../Task_BLE/Task_BLE.h"
#include "../PS_FFat/PS_FFat.h"

#define PHOTOTRANSISTOR_PIN 32

class TaskMeasure {
    public: 
        static void init();
        static void run();
    private:
        static void IRAM_ATTR TimerISR();
        static double getVoltageFromAdc(int adcReading);
        static const int ADC_PIN = 34;
        static const int LED_PIN = 22;
        static constexpr double maxVoltage = 3.9;
        static const int maxAdcReading = 4095;
        static int darkReading;
        static int activeReading;
        static hw_timer_t * timer;
        static volatile SemaphoreHandle_t timerSemaphore;
        static char timeCStr[BLE_MSG_LEN];
};

#endif /* TASK_MEASURE_H_ */

