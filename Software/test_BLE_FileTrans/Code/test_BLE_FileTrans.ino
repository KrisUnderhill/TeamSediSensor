/*
 *  This sketch demonstrates testing of BLE functionality
 *  Based existing GPIO functionality
 */

#include "Task_Measure.h"
#include "Task_BLE.h"
#include "PS_FFat.h"

#define BACKSPACE 0x7F

std::string inputString = "";
bool stringComplete = false;

void setup()
{    
    delay(1000);
    Serial.begin(115200);
    PS_FFat::init();
    TaskBLE::init();
}

void loop()
{
    TaskBLE::run();
    if(stringComplete){
        if(inputString == "readData"){
            PS_FFat::readDataFile();
        }
        inputString = "";
        stringComplete = false;
        delay(1000);
    }
}

void serialEventRun(){
    while (Serial.available()) {
        // get the new byte:
        char inChar = (char)Serial.read();
        if (inChar == '\r') {
          stringComplete = true;
          Serial.print("\r\n");
        } else if (inChar == BACKSPACE) {
            inputString.pop_back();
        } else {
            Serial.print(inChar);
            inputString += inChar;
        }
    }
}
