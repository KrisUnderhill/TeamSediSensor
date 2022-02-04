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
BLEServer* TaskBLE::p_server = NULL;
BLECharacteristic* TaskBLE::pCharacteristic = NULL;
bool TaskBLE::newVal = false;

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* p_server) {
        deviceConnected = true;
    };

    void onDisconnect(BLEServer* p_server) {
        deviceConnected = false;
    } 
};

void TaskBLE::init(){
    /* Create the BLE Device */
    BLEDevice::init("ESP32");

    /* Create the BLE Server */
    p_server = BLEDevice::createServer();
    p_server->setCallbacks(new MyServerCallbacks());

    /* creates whole service including the characteristics within this call */ 
    PS_FileXferService::createService(p_server);

    // Start advertising
    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->setScanResponse(false);
    pAdvertising->setMinPreferred(0x00);  // set value to 0x00 to not advertise this parameter
    BLEDevice::startAdvertising();
    Serial.println("Waiting a client connection to notify...");
}

void TaskBLE::run(){
    /* While Connnected */
    if (deviceConnected) {
        PS_FileXferReadChar::whileConnect();
        if(newVal){
            pCharacteristic->setValue(p_serialBuffer, serialBufferLen);
            pCharacteristic->notify();
            newVal = false;
        }
        // Note too fast will congest BT stack 
        //  hoping that the slow speed of task measure will handle this for now
    }
    /* On Disconnect */
    if (!deviceConnected && oldDeviceConnected) {
        PS_FileXferReadChar::onDisconnect();
        delay(500); // give the bluetooth stack the chance to get things ready
        p_server->startAdvertising(); // restart advertising
        Serial.println("start advertising");
        oldDeviceConnected = deviceConnected;
    }
    /* On Connect */
    if (deviceConnected && !oldDeviceConnected) {
        PS_FileXferReadChar::onConnect();

        // do stuff here on connecting
        Serial.println("New Device Connected");
        oldDeviceConnected = deviceConnected;
    }
}

void TaskBLE::setBuffer(uint8_t* p_newBuffer, size_t len){
    if(len > 0 && len < BLE_MSG_LEN){
        memcpy((void*)p_serialBuffer, (const void*)p_newBuffer, len);
        serialBufferLen = len;
    }
    newVal = true;
}