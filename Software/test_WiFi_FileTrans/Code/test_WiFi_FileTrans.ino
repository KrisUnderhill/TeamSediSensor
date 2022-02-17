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
//#include "Task_Measure.h"
//#include "Task_BLE.h"
//#include "PS_SDFile.h"
//#include "config.h"
//#include "PS_FileXferService.h"
#include "wifiServer.h"

#define BACKSPACE 0x7F

std::string inputString = "";
bool stringComplete = false;

void setup()
{    
    delay(1000);
    Serial.begin(115200);
    wifiServer::init();
}

void loop()
{
    wifiServer::run();
}

