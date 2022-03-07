#include "Arduino.h"
#include "PS_SDFile.h"
#include <MD5Builder.h>

/* file interaction functions are from the arduino SD_Test ESP32 example
 * Moved to SD card implementation from FFat on builtin spi flash
 * Modified for TSS_Sensor project by Kris Miedema
 */
#define FORMAT_FFAT true
#define DATA_FILE_NAME "/data.csv"

char PS_SDFile::p_fileBuffer[FILE_BUF_LEN] = {0};
size_t PS_SDFile::fileBufferLen = 0;

struct fileXferHeader {
    uint8_t md5sum[16];
    size_t fileSize;
};

void PS_SDFile::init(){
    if(!SD.begin()){
        Serial.println("Card Mount Failed");
        return;
    }
    writeFile(SD, (const char*)DATA_FILE_NAME, "#time, dark_ADC, dark_V, active_ADC, active_V, temp_ADC, temp_F\n");
    Serial.println("#time, dark_ADC, dark_V, active_ADC, active_V, temp_ADC, temp_F");
}

void PS_SDFile::initializeFileBuffer(uint8_t* BLEfileBuffer, size_t* BLEfileBufferLen){
    struct fileXferHeader* header = (struct fileXferHeader*) BLEfileBuffer;
    File file = SD.open("/data.csv", FILE_READ);
    MD5Builder md5;
    md5.begin();
    size_t maxLen = file.size();
    md5.addStream(file, (const size_t)maxLen);
    md5.calculate();
    md5.getBytes(header->md5sum);
    char output[33] = {0}; 
    md5.getChars(output);
    header->fileSize = maxLen;
    *BLEfileBufferLen = sizeof(*header);
    file.close();
}

void PS_SDFile::recvBuffer(uint8_t* p_destBuffer, size_t* len, size_t* offset){
    /* TODO: Make api decisions */
    memset(p_destBuffer, 0, *len);
    File file = SD.open("/data.csv", FILE_READ);
    file.seek(*offset);
    *len = file.read(p_destBuffer, *len);
    *offset = file.position();
    file.close();
}

void PS_SDFile::setBuffer(char* p_newBuffer, size_t len){
    /* TODO Decide if this is the way to go or support api to write from outside buffer */
    if(len > 0 && len < FILE_BUF_LEN){
        memcpy((void*)p_fileBuffer, (const void*)p_newBuffer, len);
        fileBufferLen = len;
    }
    appendFile(SD, (const char*)DATA_FILE_NAME, (const char *)p_fileBuffer);
}

void PS_SDFile::readDataFile(){
    PS_SDFile::readFile(SD, "/data.csv");
}

void PS_SDFile::readFile(fs::FS &fs, const char * path){
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
    Serial.println("File Read Complete");
}


void PS_SDFile::writeFile(fs::FS &fs, const char * path, const char * message){
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

void PS_SDFile::appendFile(fs::FS &fs, const char * path, const char * message){
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

void PS_SDFile::getmd5Sum(char * output, const char * path){
    File file = SD.open(path, FILE_READ);
    MD5Builder md5;
    md5.begin();
    size_t maxLen = file.size();
    md5.addStream(file, (const size_t)maxLen);
    md5.calculate();
    md5.getChars(output);
    file.close();
}

