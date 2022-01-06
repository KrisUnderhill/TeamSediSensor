#ifndef TASK_MEASURE_H_
#define TASK_MEASURE_H_

#include "Arduino.h"
#include <time.h>

class TaskMeasure {
    public: 
        TaskMeasure(){};
        void init();
        void run();
    private:
        const int POT_PIN = 34;
        const int LED_PIN = 22;
        int potReading;
};

#endif /* TASK_MEASURE_H_ */

