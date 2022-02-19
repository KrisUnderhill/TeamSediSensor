#ifndef TASK_WIFI_H_
#define TASK_WIFI_H_

/*
 * Based on arduino for ESP32 examples
 *   SDWebServer
 *   AP
 *   Modified to fit TSS Senior design project Kris Miedema
 */

#include "Arduino.h"
#include "../Config/config.h"
#include "../Task_Measure/Task_Measure.h"
#include "../PS_WifiServer/PS_WifiServer.h"
#include "../PS_FileSystem/PS_FileSystem.h"

#define BUTTON_PIN 21

class TaskWifi {
    public: 
        static void init();
        static void run();
        static void resumeTask() { taskRunning = true;  }
        static void pauseTask()  { taskRunning = false; }

    private:
        static void startServer();
        static void stopServer();
        static void IRAM_ATTR buttonInt();

        static volatile bool startWifi;
        static volatile bool runningWifi;
        static volatile bool taskRunning;
};
#endif /* TASK_WIFI_H_ */

