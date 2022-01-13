/*
 *  This sketch demonstrates testing of BLE functionality
 *  Based existing GPIO functionality
 */

#include "Task_Measure.h"
#include "Task_BLE.h"
#include "PS_FFat.h"

#define BACKSPACE 0x7F

/* Stupid global vars I can't seem to get rid of yet */
TaskMeasure taskM;
TaskBLE taskB;
PS_FFat ps_fs;

std::string inputString = "";
bool stringComplete = false;

void setup()
{    
    delay(1000);
    Serial.begin(115200);
    ps_fs.init();
    taskM.init();
    taskB.init();
}

void loop()
{
    taskM.run();
    taskB.run();
    if(stringComplete){
        if(inputString == "readData"){
            ps_fs.readDataFile();
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
