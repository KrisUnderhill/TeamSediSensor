#ifndef TASK_BLE_H_
#define TASK_BLE_H_

#include "Arduino.h"
#include "SimpleBLE.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
    #error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

class TaskBLE {
    public: 
        static void init();
        static void run();
    private:
        static SimpleBLE ble;
        static void IRAM_ATTR TimerISR();
        static hw_timer_t * timer;
        static volatile SemaphoreHandle_t timerSemaphore;
};

#endif /* TASK_MEASURE_H_ */

