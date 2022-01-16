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
uint8_t TaskBLE::p_msgBuffer[BLE_MSG_LEN] = {0};
size_t TaskBLE::msgBufferLen = 0;
BLEServer* TaskBLE::pServer = NULL;
BLECharacteristic* TaskBLE::pCharacteristic = NULL;
bool TaskBLE::newVal = false;
BLECharacteristic* TaskBLE::p_ftCharacteristic = NULL;

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* p_Server) {
        deviceConnected = true;
    };

    void onDisconnect(BLEServer* p_Server) {
        deviceConnected = false;
    } 
};

class desc2902Callbacks: public BLEDescriptorCallbacks {
    void onRead(BLEDescriptor* pDescriptor){
        Serial.println("HELLO From DESC on read");
        Serial.println(pDescriptor->toString().c_str());
    }
	void onWrite(BLEDescriptor* pDescriptor){
        Serial.println("HELLO From DESC on read");
        Serial.println(pDescriptor->toString().c_str());
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
    //pCharacteristic = pService->createCharacteristic(
    //                    CHARACTERISTIC_UUID,
    //                    BLECharacteristic::PROPERTY_READ  |
    //                    BLECharacteristic::PROPERTY_NOTIFY 
    //                  );

    // https://www.bluetooth.com/specifications/gatt/viewer?attributeXmlFile=org.bluetooth.descriptor.gatt.client_characteristic_configuration.xml
    // Create a BLE Descriptor
    //pCharacteristic->addDescriptor(new BLE2902());

    // Create a BLE Characteristic
    p_ftCharacteristic = pService->createCharacteristic(
                         FT_CHAR_UUID,
                         BLECharacteristic::PROPERTY_READ    |
                         BLECharacteristic::PROPERTY_INDICATE
                       );
    Serial.println(p_ftCharacteristic->toString().c_str());


    // Create a BLE Descriptor
    p_ftCharacteristic->addDescriptor(new BLE2902());
    BLEDescriptor* p_ft_Descriptor2902 = p_ftCharacteristic->getDescriptorByUUID(BLEUUID((uint16_t) 0x2902));
    p_ft_Descriptor2902->setCallbacks(new desc2902Callbacks());

    // Start the service
    pService->start();
    Serial.println(pService->toString().c_str());
    BLECharacteristic* p_testChar = pService->getCharacteristic("beb5483e-36e1-4688-b7f5-ea07361b26a8");
    if(p_testChar != nullptr) {
        Serial.println(p_testChar->toString().c_str());
    } else {
        Serial.println("Was Null");
    }

    // Start advertising
    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->setScanResponse(false);
    pAdvertising->setMinPreferred(0x00);  // set value to 0x00 to not advertise this parameter
                                          // I'm guessing some of the linux problems could be fixed 
                                          // looking into these
    BLEDevice::startAdvertising();
    Serial.println("Waiting a client connection to notify...");
}

void TaskBLE::run(){
    // notify changed value
    if (deviceConnected && newVal) {
        p_ftCharacteristic->setValue(p_msgBuffer, (size_t)msgBufferLen);
        p_ftCharacteristic->notify(false);
        //pCharacteristic->setValue(p_msgBuffer, (size_t)msgBufferLen);
        //pCharacteristic->notify();
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
}

void TaskBLE::setBuffer(uint8_t* p_newBuffer, size_t len){
    if(len > 0 && len < BLE_MSG_LEN){
        memcpy((void*)p_msgBuffer, (const void*)p_newBuffer, len);
        msgBufferLen = len;
    }
    newVal = true;
}
