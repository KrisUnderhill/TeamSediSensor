#ifndef TASK_BLE_H_
#define TASK_BLE_H_

#include "Arduino.h"
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

#define MSG_LEN 50

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
        void init();
        void run();
        void setBuffer(uint8_t* p_newBuffer, size_t len);
    private:
        uint8_t p_msgBuffer[MSG_LEN] = {0};
        size_t msgBufferLen = 0;
        BLEServer* pServer = NULL;
        BLECharacteristic* pCharacteristic = NULL;
};
#endif /* TASK_BLE_H_ */

