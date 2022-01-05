/* Task_Measure.cpp 
 * Turns on the LED and Phototransistor 
 * reads data off the adc pins
 */

#include "Arduino.h"
#include "Task_Measure.h"

void TaskMeasure::init(){
    Serial.begin(115200);
    //pinMode(POT_PIN, INPUT)
    pinMode(LED_PIN, OUTPUT);

    Serial.println("Setup done");
}

void TaskMeasure::run(){
    //turn on LED
    digitalWrite(LED_PIN, HIGH);
    potReading = analogRead(POT_PIN);
    Serial.println("READING");
    Serial.println(potReading);
    // Wait 
    delay(1000);
    //turn off
    digitalWrite(LED_PIN, LOW);
    // wait
    delay(1000);
}

