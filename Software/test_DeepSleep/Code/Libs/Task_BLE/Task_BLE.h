#ifndef TASK_BLE_H_
#define TASK_BLE_H_

#include "Arduino.h"
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include "../Config/config.h"
#include "../PS_FFat/PS_FFat.h"
#include "../PS_FileXferService/PS_FileXferService.h"

/* bluetoothctl man menu scan
    uuids 4fafc201-1fb5-459e-8fcc-c5c9c331914b beb5483e-36e1-4688-b7f5-ea07361b26a8 (array[strings]) -> filter to only these uuids
    RSSI -50 (int16) -> filter results to only those w/ RSSI (Received signal strength)
    pathloss uint16 -> filter results to only with tx stronger than specified (I think?)
    duplicateData bool -> disable or enable duplicate detection of advertisement data 
    discoverable bool -> make adapter discoverable or not
    pattern string -> if pattern matches prefix address or device name 
    * Calling any without parameter gives its values
*/

class TaskBLE {
    public: 
        static void init();
        static void run();
        static void setBuffer(uint8_t* p_newBuffer, size_t len);
    private:
        static uint8_t p_serialBuffer[BLE_MSG_LEN];
        static size_t serialBufferLen;
        static BLEServer* p_server;
        static BLECharacteristic* pCharacteristic;
        static bool newVal;
};
#endif /* TASK_BLE_H_ */

