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
#include "../Config/config.h" /* Include path for lib */

volatile bool TaskBLE::deviceConnected = false;
volatile bool TaskBLE::oldDeviceConnected = false;


class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* p_Server) {
        TaskBLE::deviceConnected = true;
    };

    void onDisconnect(BLEServer* p_Server) {
        TaskBLE::deviceConnected = false;
    } /* should this be a ; */
};

TaskBLE::TaskBLE(){
    p_Server = NULL;
    p_Service = NULL;
    p_Characteristic = NULL;
    value = 0x1000000;
}

void TaskBLE::init(){
    BLEDevice::init("TSS Sensor");
    p_Server = BLEDevice::createServer();
    p_Service = p_Server->createService(SERVICE_UUID);
    p_Characteristic = p_Service->createCharacteristic(
                       CHARACTERISTIC_UUID,
                       BLECharacteristic::PROPERTY_READ   |
                       BLECharacteristic::PROPERTY_WRITE  |
                       BLECharacteristic::PROPERTY_NOTIFY |
                       BLECharacteristic::PROPERTY_INDICATE 
                      );

   p_Characteristic->setValue((uint8_t*)&value, 4);
   p_Characteristic->addDescriptor(new BLE2902());

    p_Service->start();

    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->setScanResponse(false);
    pAdvertising->setMinPreferred(0x0);
    BLEDevice::startAdvertising();
    Serial.println("Waiting for a client to notify");
    Serial.printf("Is device connected? %s\r\n", deviceConnected ? "true" : "false"); 
}

void TaskBLE::run(){
    // notify changed value
    if (deviceConnected) {
        Serial.println("Connected to device");
        p_Characteristic->setValue((uint8_t*)&value, 4);
        p_Characteristic->notify();
        value++;
        delay(1000); // bluetooth stack will go into congestion, if too many packets are sent, in 6 hours test i was able to go as low as 3ms
    }
    // disconnecting
    if (!deviceConnected && oldDeviceConnected) {
        delay(500); // give the bluetooth stack the chance to get things ready
        p_Server->startAdvertising(); // restart advertising
        Serial.println("start advertising");
        oldDeviceConnected = deviceConnected;
    }
    // connecting
    if (deviceConnected && !oldDeviceConnected) {
        // do stuff here on connecting
        oldDeviceConnected = deviceConnected;
    }
}
