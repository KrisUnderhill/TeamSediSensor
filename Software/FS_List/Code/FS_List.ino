#include "FS.h"
#include "FFat.h"

// This file should be compiled with 'Partition Scheme' (in Tools menu)
// set to 'Default with ffat' if you have a 4MB ESP32 dev module or
// set to '16M Fat' if you have a 16MB ESP32 dev module.

// You only need to format FFat the first time you run a test
#define FORMAT_FFAT false

void listDir(fs::FS &fs, const char * dirname, uint8_t levels){
    Serial.printf("Listing directory: %s\r\n", dirname);

    File root = fs.open(dirname);
    if(!root){
        Serial.println("- failed to open directory");
        return;
    }
    if(!root.isDirectory()){
        Serial.println(" - not a directory");
        return;
    }

    File file = root.openNextFile();
    while(file){
        if(file.isDirectory()){
            Serial.print("  DIR : ");
            Serial.println(file.name());
            if(levels){
                listDir(fs, file.name(), levels -1);
            }
        } else {
            Serial.print("  FILE: ");
            Serial.print(file.name());
            Serial.print("\tSIZE: ");
            Serial.println(file.size());
            readFile(FFat, (const char *)file.name());
        }
        file = root.openNextFile();
    }
}

void readFile(fs::FS &fs, const char * path){
    Serial.printf("Reading file: %s\r\n", path);

    File file = fs.open(path);
    if(!file || file.isDirectory()){
        Serial.println("- failed to open file for reading");
        return;
    }

    Serial.println("- read from file:");
    char readChar;
    size_t len = 1;
    //while(file.available()){
    for(int i = 0; i < 200; i++){
        file.readBytes(&readChar, len);
        if(readChar == '\n') {
            Serial.print("\r\n");
        } else {
            Serial.print(readChar);
        }
    }
    file.close();
}

void setup(){
    delay(2000);
    Serial.begin(115200);
    Serial.setDebugOutput(true);
    if (FORMAT_FFAT) FFat.format();
    if(!FFat.begin()){
        Serial.println("FFat Mount Failed");
        return;
    }

    Serial.printf("Total space: %10u\r\n", FFat.totalBytes());
    Serial.printf("Free space: %10u\r\n", FFat.freeBytes());
    listDir(FFat, "/", 0);
}

void loop(){

}
