#ifndef TASK_WIFI_H_
#define TASK_WIFI_H_

/*
 * Based on arduino for ESP32 examples
 *   SDWebServer
 *   AP
 *   Modified to fit TSS Senior design project Kris Miedema
 */

#include "Arduino.h"
extern "C" {
#include "esp_timer.h"
}
#include "../Config/config.h"
#include "../Task_Measure/Task_Measure.h"
#include "../PS_WifiServer/PS_WifiServer.h"
#include "../PS_FileSystem/PS_FileSystem.h"

#define BUTTON_PIN 33

class TaskWifi {
    public: 
        static void fullInit();
        static void wakeInit();
        static void run();
        static void resumeTask() { taskRunning = true;  }
        static void pauseTask()  { taskRunning = false; }
        static bool getReadyToSleep() { return readyToSleep; }
        static void callIntr() { buttonInt(); }
    private:
        static void startServer();
        static void stopServer();
        static void IRAM_ATTR buttonInt();

        static volatile bool startWifi;
        static volatile bool runningWifi;
        static volatile bool stopWifi;
        static volatile bool taskRunning;
        static bool readyToSleep;

        static esp_timer_handle_t shutOffTimer;
        static void shutOffTimerCallback(void* args);
        static esp_timer_create_args_t shutOffTimerArgs;
};
#endif /* TASK_WIFI_H_ */

