#include "Arduino.h"
#include "PS_FileSystem.h"
#include <MD5Builder.h>
#include "webFiles.h"

/* file interaction functions are from the arduino SD_Test ESP32 example
 * Moved to SD card implementation from FFat on builtin spi flash
 * Modified for TSS_Sensor project by Kris Miedema
 */

fs::FS PS_FileSystem::fileSystem = SD;
uint16_t PS_FileSystem::fileLocks = 0;

void PS_FileSystem::init(){
    if(!fileSystem.begin()){
        Serial.println("FileSystem Mount Failed");
        return;
    }
    //writeFile(fileSystem, (const char*)DATA_FILE_NAME, "#time, dark_ADC, dark_V, active_ADC, active_V, temp_ADC, temp_F\n");
    //Serial.println("#time, dark_ADC, dark_V, active_ADC, active_V, temp_ADC, temp_F");
}

File PS_FileSystem::open(const char* path, int mode){
    /* check fsGood */
    /* check locks */
    /* get file */
    File f;
    return f;
}

void PS_FileSystem::getmd5Sum(char * output, const char* path){
    File file = fileSystem.open(path, FILE_READ);
    MD5Builder md5;
    md5.begin();
    size_t maxLen = file.size();
    md5.addStream(file, (const size_t)maxLen);
    md5.calculate();
    md5.getChars(output);
    file.close();
}

void PS_FileSystem::getmd5Sum(char* output, char* str, uint16_t len){
    MD5Builder md5;
    md5.begin();
    md5.add((uint8_t*)str, len);
    md5.calculate();
    md5.getChars(output);
}

bool PS_FileSystem::verifyFileSystem(){
    char expectedHash[33];
    char gotHash[33];
    for(int i = 0; i < numFiles; i++){
        if(fileSystem.exists(genFiles[i].name)){
            File f = fileSystem.open(genFiles[i].name);
            if(f.size() == genFiles[i].size){
                size_t lenExpected = strlen(genFiles[i].name);
                if(strncmp(f.name(), genFiles[i].name, lenExpected) == 0) {
                    Serial.printf("Found File: %s\r\n", f.name());
                    getmd5Sum(expectedHash, genFiles[i].contents, genFiles[i].size);
                    getmd5Sum(gotHash, f.name());
                    Serial.println(expectedHash);
                    Serial.println(gotHash);
                    if(strncmp(expectedHash,gotHash, 33) == 0)
                        continue;
                }
            }
        }
        writeExpectedFile(i);
    }
    fsGood = true;
    return fsGood;
}

bool PS_FileSystem::writeExpectedFile(int expectedFileIndex){
    File f = fileSystem.open(genFiles[expectedFileIndex].name, FILE_WRITE);
    f.write((uint8_t*)genFiles[expectedFileIndex].contents, genFiles[expectedFileIndex].size);
    f.close();
    return true;
}

//void PS_FileSystem::readFile(fs::FS &fs, const char * path){
//    Serial.printf("Reading file: %s\r\n", path);
//
//    File file = fs.open(path);
//    if(!file || file.isDirectory()){
//        Serial.println("- failed to open file for reading");
//        return;
//    }
//
//    Serial.println("- read from file:");
//    char readChar;
//    size_t len = 1;
//    while(file.available()){
//        file.readBytes(&readChar, len);
//        if(readChar == '\n') {
//            Serial.print("\r\n");
//        } else {
//            Serial.print(readChar);
//        }
//    }
//    file.close();
//    Serial.println("File Read Complete");
//}
//
//
//void PS_FileSystem::writeFile(fs::FS &fs, const char * path, const char * message){
//    //Serial.printf("Writing file: %s\r\n", path);
//
//    File file = fs.open(path, FILE_WRITE);
//    if(!file){
//        Serial.println("- failed to open file for writing");
//        return;
//    }
//    if(file.print(message)){
//        //Serial.println("- file written");
//    } else {
//        Serial.println("- write failed");
//    }
//    file.close();
//}
//
//void PS_FileSystem::appendFile(fs::FS &fs, const char * path, const char * message){
//    //Serial.printf("Appending to file: %s\r\n", path);
//
//    File file = fs.open(path, FILE_APPEND);
//    if(!file){
//        Serial.println("- failed to open file for appending");
//        return;
//    }
//    if(file.print(message)){
//        //Serial.println("- message appended");
//    } else {
//        Serial.println("- append failed");
//    }
//    file.close();
//}

