/*
 *  This sketch demonstrates testing of GPIO functionality
 *  For project buliding
 */

#include "Task_Measure.h"

/* Stupid global vars I can't seem to get rid of yet */
TaskMeasure taskM;

void setup()
{    
    Serial.begin(115200);
    taskM.init();
}

void loop()
{
    taskM.run();
}

