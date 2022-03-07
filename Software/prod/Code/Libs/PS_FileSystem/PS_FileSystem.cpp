#include "Arduino.h"
#include "PS_FileSystem.h"
#include <MD5Builder.h>
#include "webFiles.h"

/* file interaction functions are from the arduino SD_Test ESP32 example
 * Moved to SD card implementation from FFat on builtin spi flash
 * Modified for TSS_Sensor project by Kris Miedema
 */

uint16_t PS_FileSystem::fileLocks = 0;

void PS_FileSystem::fullInit(){
    if(!fileSystem.begin()){
        Serial.println("FileSystem Mount Failed");
        return;
    }
    verifyFileSystem();
}

void PS_FileSystem::wakeInit(){
    if(!fileSystem.begin()){
        Serial.println("FileSystem Mount Failed");
        return;
    }
}

bool PS_FileSystem::open(File* f, int index, const char*  mode){
    /* check locks */
    if((fileLocks & (1 << index)) == 0) {
        fileLocks = (fileLocks & (1 << index));
        *f = fileSystem.open(genFiles[index].name, mode);
        return true;
    }
    return false;
}

void PS_FileSystem::close(int index){
    fileLocks = (fileLocks & (~(1<<index)));
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

void PS_FileSystem::verifyFileSystem(){
    char expectedHash[33];
    char gotHash[33];
    for(int i = 0; i < numFiles; i++){
        if(fileSystem.exists(genFiles[i].name)){
            File f = fileSystem.open(genFiles[i].name);
            if(f.size() == genFiles[i].size){
                Serial.printf("Found File: %s\r\n", f.name());
                size_t lenExpected = strlen(genFiles[i].name);
                if(strncmp(f.name(), genFiles[i].name, lenExpected) == 0) {
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
}

void PS_FileSystem::writeExpectedFile(int expectedFileIndex){
    File f = fileSystem.open(genFiles[expectedFileIndex].name, FILE_WRITE);
    f.write((uint8_t*)genFiles[expectedFileIndex].contents, genFiles[expectedFileIndex].size);
    f.close();
}

