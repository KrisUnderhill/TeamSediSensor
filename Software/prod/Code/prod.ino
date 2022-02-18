/*
 *  This sketch is the production intent software
 *  Powers the Phototransistor + amplifier 
 *  Controls the LED
 *  reads data from the ADC
 */

/* Arduino IDE will only compile libraries it knows are being used in the *.ino file
 * Hence if a library isn't listed here it will not be compiled 
 * Because I'm using libraries in other libraries I'm just listing them here 
 * until I find a better way. Even if they are not used here necessarily
 */
#include "Task_Measure.h"
#include "PS_SDFile.h"
#include "config.h"
#include "Task_Wifi.h"
#include "wifiServer.h"

#define BACKSPACE 0x7F

std::string inputString = "";
bool stringComplete = false;

void setup()
{    
    delay(1000);
    Serial.begin(115200);
    TaskMeasure::init();
    TaskWifi::init();
}

void loop()
{
    /* TODO debug TaskMeasure and Task_Wifi  message passing
     * especially semaphores to protect file access
     */
    TaskMeasure::run(); 
    TaskWifi::run();
    /* Handle serial commands */
    if(stringComplete){
        if(inputString == "readData"){
            PS_SDFile::readDataFile();
        }
        inputString = "";
        stringComplete = false;
        delay(1000);
    }
}

/* Run on serial event (char arrived) */
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
