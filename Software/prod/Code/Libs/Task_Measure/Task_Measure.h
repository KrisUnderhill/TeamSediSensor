#ifndef TASK_MEASURE_H_
#define TASK_MEASURE_H_

#include "Arduino.h"
#include <time.h>
#include "../PS_FileSystem/PS_FileSystem.h"

#define PHOTOTRANSISTOR_PIN 32
#define MSG_LEN 500

class TaskMeasure {
    public: 
        static void fullInit();
        static void wakeInit();
        static void run();
        static void pauseTask() { taskRunning = false; }
        static void resumeTask() { taskRunning = true; }
        static bool getReadyToSleep() { return readyToSleep; }
        static int64_t getTimeToSleep() { return (nextRun - getuSecs()); }
        static char* getMeasure() { return timeCStr; }
    private:
        static int64_t getuSecs();
        static void IRAM_ATTR TimerISR();
        static double getVoltageFromAdc(int adcReading);
        static double getTempFromAdc(int adcReading);
        static const int ADC_PIN = 34;
        static const int LED_PIN = 22;
        static const int TEMP_PIN = 39;
        static constexpr double maxVoltage = 3.3;
        static const int maxAdcReading = 4095;
        static constexpr float VOLTS_PER_DEG = 0.010;
        static int darkReading;
        static int activeReading;
        static int tempAdc;
        static hw_timer_t * timer;
        static volatile SemaphoreHandle_t timerSemaphore;
        static char timeCStr[MSG_LEN];
        static bool readyToSleep;
        static volatile bool taskRunning;
        static RTC_DATA_ATTR int64_t nextRun;
};

#endif /* TASK_MEASURE_H_ */

