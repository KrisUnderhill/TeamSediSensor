#include "Arduino.h"
#include "PS_FFat.h"

void PS_FFat::init(){
    if(FORMAT_FFAT) 
    {   
        Serial.println(FORMAT_FFAT);
        FFat.format();
    }
    if(!FFat.begin()){
        Serial.println("FFat Mount Failed");
        return;
    }

    Serial.printf("Total space: %10u\n", FFat.totalBytes());
    Serial.printf("Free space: %10u\n", FFat.freeBytes());
}

void PS_FFat::recvBuffer(uint8_t* p_destBuffer, size_t* len){
    //if(len > 0 && len < MSG_LEN){
    //    memcpy((void*)p_msgBuffer, (const void*)p_newBuffer, len);
    //    msgBufferLen = len;
    //}
}

void PS_FFat::setBuffer(uint8_t* p_newBuffer, size_t len){
    //if(len > 0 && len < MSG_LEN){
    //    memcpy((void*)p_msgBuffer, (const void*)p_newBuffer, len);
    //    msgBufferLen = len;
    //}
}

