/*
    Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleNotify.cpp
    Ported to Arduino ESP32 by Evandro Copercini
    updated by chegewara
    Modified to fit TSS Senior design project Kris Miedema

    Create a BLE server that, once we receive a connection, will send periodic notifications.
    The service advertises itself as: 4fafc201-1fb5-459e-8fcc-c5c9c331914b
    And has a characteristic of: beb5483e-36e1-4688-b7f5-ea07361b26a8
*/


#include "Arduino.h"
#include "Task_BLE.h"
#include <cstring>

bool deviceConnected = false;
bool oldDeviceConnected = false;
uint8_t TaskBLE::p_serialBuffer[BLE_MSG_LEN] = {0};
size_t TaskBLE::serialBufferLen = 0;
uint8_t TaskBLE::p_fileXferBuffer[BLE_MSG_LEN] = {0};
size_t TaskBLE::fileXferBufferLen = 0;
size_t TaskBLE::offset = 0;
size_t TaskBLE::full_fileSize = 0;
BLEServer* TaskBLE::pServer = NULL;
BLECharacteristic* TaskBLE::pCharacteristic = NULL;
bool TaskBLE::newVal = false;
BLECharacteristic* TaskBLE::p_ftCharacteristic = NULL;
volatile bool TaskBLE::startFT = false;
volatile bool TaskBLE::newIndicate = false;

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* p_Server) {
        deviceConnected = true;
    };

    void onDisconnect(BLEServer* p_Server) {
        deviceConnected = false;
    } 
};

class startIndicateOnRead: public BLEDescriptorCallbacks {
	void onWrite(BLEDescriptor* pDescriptor){
        /* This callback is called whenever the descriptor is read 
         *   when Linux requests notifications/indications it reads the descriptor
         *   Hence start sending indications on this act 
         */
        TaskBLE::startFT = true;
    }
};

class FT_Callbacks : public BLECharacteristicCallbacks {
    void onStatus(BLECharacteristic* pCharacteristic, Status s, uint32_t code){
        switch(s) {
            case SUCCESS_INDICATE: {
                TaskBLE::newIndicate = true;
                break;
            }
            /* intentionally letting things fall through here */
		    case ERROR_INDICATE_DISABLED:
		    case ERROR_NOTIFY_DISABLED:
		    case ERROR_GATT:
            case ERROR_NO_CLIENT:
            case ERROR_INDICATE_TIMEOUT:
            case ERROR_INDICATE_FAILURE: {
                if(TaskBLE::startFT)
                    TaskBLE::startFT = false;
                break;
            } 
            default: {
                break;
            }
        }

    }
};

void TaskBLE::init(){
    // Create the BLE Device
    BLEDevice::init("ESP32");

    // Create the BLE Server
    pServer = BLEDevice::createServer();
    pServer->setCallbacks(new MyServerCallbacks());

    // Create the BLE Service
    BLEService *pService = pServer->createService(SERVICE_UUID);

    // Create a BLE Characteristic
    pCharacteristic = pService->createCharacteristic(
                        SERIAL_CHAR_UUID,
                        BLECharacteristic::PROPERTY_READ  |
                        BLECharacteristic::PROPERTY_NOTIFY 
                      );

    // https://www.bluetooth.com/specifications/gatt/viewer?attributeXmlFile=org.bluetooth.descriptor.gatt.client_characteristic_configuration.xml
    // Create a BLE Descriptor
    pCharacteristic->addDescriptor(new BLE2902());

    // Create a BLE Characteristic
    p_ftCharacteristic = pService->createCharacteristic(
                         FT_CHAR_UUID,
                         BLECharacteristic::PROPERTY_READ    |
                         BLECharacteristic::PROPERTY_INDICATE
                       );

    p_ftCharacteristic->setCallbacks(new FT_Callbacks());

    // Create a BLE Descriptor
    p_ftCharacteristic->addDescriptor(new BLE2902());
    BLEDescriptor* p_ft_Descriptor2902 = p_ftCharacteristic->getDescriptorByUUID(BLEUUID((uint16_t) 0x2902));
    p_ft_Descriptor2902->setCallbacks(new startIndicateOnRead());

    // Start the service
    pService->start();

    PS_FFat::initializeFileBuffer(p_fileXferBuffer, &fileXferBufferLen); 
    p_ftCharacteristic->setValue(p_fileXferBuffer, fileXferBufferLen);

    // Start advertising
    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->setScanResponse(false);
    pAdvertising->setMinPreferred(0x00);  // set value to 0x00 to not advertise this parameter
    BLEDevice::startAdvertising();
    Serial.println("Waiting a client connection to notify...");
}

void TaskBLE::run(){
    // notify changed value
    if (deviceConnected && newVal) {
        pCharacteristic->setValue(p_serialBuffer, serialBufferLen);
        pCharacteristic->notify();
        newVal = false;
        // Note too fast will congest BT stack 
        //  hoping that the slow speed of task measure will handle this for now
    }
    // disconnecting
    if (!deviceConnected && oldDeviceConnected) {
        delay(500); // give the bluetooth stack the chance to get things ready
        pServer->startAdvertising(); // restart advertising
        Serial.println("start advertising");
        oldDeviceConnected = deviceConnected;
    }
    // connecting
    if (deviceConnected && !oldDeviceConnected) {
        // do stuff here on connecting
        Serial.println("New Device Connected");
        oldDeviceConnected = deviceConnected;
    }

    if(startFT) {
        p_ftCharacteristic->indicate();
        full_fileSize = p_fileXferBuffer[16] + (p_fileXferBuffer[17] << 8);
    }
    if(newIndicate){
        if(offset == full_fileSize) {
            Serial.println("File Xfer Complete");
        } else {
            PS_FFat::recvBuffer(p_fileXferBuffer, &fileXferBufferLen, &offset);
            p_ftCharacteristic->setValue(p_fileXferBuffer, fileXferBufferLen);
            p_ftCharacteristic->indicate();
        }

        newIndicate = false;
    }
}

void TaskBLE::setBuffer(buf_ID bufferID, uint8_t* p_newBuffer, size_t len){
    uint8_t * p_buffer = NULL;
    size_t * bufferLen = NULL;
    if(bufferID == SERIAL_BUF) {
        p_buffer = p_serialBuffer;
        bufferLen = &serialBufferLen;
    } else if(bufferID == FILE_XFER_BUF) {
        p_buffer = p_fileXferBuffer;
        bufferLen = &fileXferBufferLen;
    } else {}

    if(len > 0 && len < BLE_MSG_LEN && p_buffer != NULL){
        memcpy((void*)p_buffer, (const void*)p_newBuffer, len);
        *bufferLen = len;
    }
    if(p_buffer == p_serialBuffer) {
        newVal = true;
    }
}
