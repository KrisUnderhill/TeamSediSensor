#include "Arduino.h"
#include "PS_FFat.h"

/* file interaction functions are from the arduino FFat_Test ESP32 example
 * Modified for TSS_Sensor project by Kris Miedema
 */

char PS_FFat::p_fileBuffer[FILE_BUF_LEN] = {0};
size_t PS_FFat::fileBufferLen = 0;

void PS_FFat::init(){
    if(FORMAT_FFAT) FFat.format();
    if(!FFat.begin()){
        Serial.println("FFat Mount Failed");
        return;
    }
    PS_FFat::writeFile(FFat, (const char *)DATA_FILE_NAME, "#time, ADC Voltage,\n");
}

void PS_FFat::recvBuffer(char* p_destBuffer, size_t* len){
    /* TODO: Decide how to do this read section of a file */
    //if(len > 0 && len < MSG_LEN){
    //    memcpy((void*)p_msgBuffer, (const void*)p_newBuffer, len);
    //    msgBufferLen = len;
    //}
}

void PS_FFat::setBuffer(char* p_newBuffer, size_t len){
    /* TODO Decide if this is the way to go or support api to write from outside buffer */
    if(len > 0 && len < FILE_BUF_LEN){
        memcpy((void*)p_fileBuffer, (const void*)p_newBuffer, len);
        fileBufferLen = len;
    }
    PS_FFat::appendFile(FFat, (const char*)DATA_FILE_NAME, (const char *)p_fileBuffer);
}

void PS_FFat::readDataFile(){
    PS_FFat::readFile(FFat, DATA_FILE_NAME);
}

void PS_FFat::readFile(fs::FS &fs, const char * path){
    Serial.printf("Reading file: %s\r\n", path);

    File file = fs.open(path);
    if(!file || file.isDirectory()){
        Serial.println("- failed to open file for reading");
        return;
    }

    Serial.println("- read from file:");
    char readChar;
    size_t len = 1;
    while(file.available()){
        file.readBytes(&readChar, len);
        if(readChar == '\n') {
            Serial.print("\r\n");
        } else {
            Serial.print(readChar);
        }
    }
    file.close();
}

void PS_FFat::writeFile(fs::FS &fs, const char * path, const char * message){
    //Serial.printf("Writing file: %s\r\n", path);

    File file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("- failed to open file for writing");
        return;
    }
    if(file.print(message)){
        //Serial.println("- file written");
    } else {
        Serial.println("- write failed");
    }
    file.close();
}

void PS_FFat::appendFile(fs::FS &fs, const char * path, const char * message){
    //Serial.printf("Appending to file: %s\r\n", path);

    File file = fs.open(path, FILE_APPEND);
    if(!file){
        Serial.println("- failed to open file for appending");
        return;
    }
    if(file.print(message)){
        //Serial.println("- message appended");
    } else {
        Serial.println("- append failed");
    }
    file.close();
}

