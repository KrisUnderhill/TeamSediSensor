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
#include <cstring>

bool deviceConnected = false;
bool oldDeviceConnected = false;

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* p_Server) {
        deviceConnected = true;
    };

    void onDisconnect(BLEServer* p_Server) {
        deviceConnected = false;
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
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_READ  |
                      BLECharacteristic::PROPERTY_NOTIFY 
                    );

  // https://www.bluetooth.com/specifications/gatt/viewer?attributeXmlFile=org.bluetooth.descriptor.gatt.client_characteristic_configuration.xml
  // Create a BLE Descriptor
  pCharacteristic->addDescriptor(new BLE2902());

  // Start the service
  pService->start();

  // Start advertising
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(false);
  pAdvertising->setMinPreferred(0x00);  // set value to 0x00 to not advertise this parameter
                                        // I'm guessing some of the linux problems could be fixed 
                                        // looking into these
  BLEDevice::startAdvertising();
  Serial.println("Waiting a client connection to notify...");
  char test[]{"HELLO WORLD"};

  this->setBuffer((uint8_t*)test, strlen(test));
}

void TaskBLE::run(){
    // notify changed value
    if (deviceConnected) {
        pCharacteristic->setValue(p_msgBuffer, (size_t)msgBufferLen);
        pCharacteristic->notify();
        delay(100); // bluetooth stack will go into congestion, if too many packets are sent, in 6 hours test i was able to go as low as 3ms
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
}

void TaskBLE::setBuffer(uint8_t* p_newBuffer, size_t len){
    if(len > 0 && len < MSG_LEN){
        memcpy((void*)p_msgBuffer, (const void*)p_newBuffer, len);
        msgBufferLen = len;
    }
}
