#ifndef TASK_MEASURE_H_
#define TASK_MEASURE_H_

#include "Arduino.h"
#include <time.h>
#include "../Task_BLE/Task_BLE.h"

class TaskMeasure {
    public: 
        static void init();
        static void run();
    private:
        static void IRAM_ATTR TimerISR();
        static const int POT_PIN = 34;
        static const int LED_PIN = 22;
        static int potReading;
        static hw_timer_t * timer;
        static volatile SemaphoreHandle_t timerSemaphore;
        static char timeCStr[MSG_LEN];
        static TaskBLE taskB;
};

#endif /* TASK_MEASURE_H_ */

