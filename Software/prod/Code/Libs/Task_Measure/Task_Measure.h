#ifndef TASK_MEASURE_H_
#define TASK_MEASURE_H_

#include "Arduino.h"
#include <time.h>
#include <vector>
#include "../PS_FileSystem/PS_FileSystem.h"

/* Pins */
#define PHOTOTRANSISTOR_PIN 32
#define ADC_PIN 34 /* Phototransistor ADC */
#define LED_PIN 22
#define TEMP_PIN 39
#define BATT_PIN 35

/* Calculation Constants */
#define VOLTS_PER_DEG 0.010
#define MAX_VOLTAGE 3.3
#define MAX_ADC_READING 4095

/* Wait Times */
#define WAIT_PHOTOTRANSISTOR_ON_TO_AMB_MEASURE 100
#define WAIT_AMB_MEASURE_TO_LED_ON 50
#define WAIT_LED_ON_TO_ACT_MEASURE 100 
#define WAIT_ACT_MEASURE_TO_LED_OFF 50

#define MSG_LEN 500

enum TaskMeasureStates {WAITING, AMB_MEASURE, LED_ON, ACT_MEASURE, LED_OFF, COMPUTE_MEASURE};

class TaskMeasure {
    public: 
        static void fullInit();
        static void wakeInit();
        static void run();
        static bool getReadyToSleep() { return readyToSleep; }
        static int64_t getTimeToSleep() { return (nextRun - getuSecs()); }
        static char* getMeasure() { return timeCStr; }
    private:
        static int64_t getuSecs();
        static void IRAM_ATTR TimerISR();
        static double getVoltageFromAdc(int adcReading);
        static double getTempFromAdc(int adcReading);
        static std::vector<int> darkReading_v;
        static std::vector<int> actReading_v;
        static std::vector<int> tempAdc_v;
        static std::vector<int> battAdc_v;

        static char timeCStr[MSG_LEN];
        static bool readyToSleep;
        static volatile bool taskRunning;
        static RTC_DATA_ATTR int64_t nextRun;
        static unsigned long lastStateChange;
        static enum TaskMeasureStates taskMeasureState;
        static int stateIndex;
};

#endif /* TASK_MEASURE_H_ */

