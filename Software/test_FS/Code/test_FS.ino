/*
 *  This sketch demonstrates testing of BLE functionality
 *  Based existing GPIO functionality
 */

#include "Task_Measure.h"
#include "Task_BLE.h"
#include "PS_FFat.h"

/* Stupid global vars I can't seem to get rid of yet */
//TaskMeasure taskM;
//TaskBLE taskB;
PS_FFat ps_fs;

void setup()
{    
    delay(1000);
    Serial.begin(115200);
    ps_fs.init();
    //taskM.init();
    //taskB.init();
}

void loop()
{
    //taskM.run();
    //taskB.run();
    Serial.println("Well at least it's looping?");
    delay(1500);
}

