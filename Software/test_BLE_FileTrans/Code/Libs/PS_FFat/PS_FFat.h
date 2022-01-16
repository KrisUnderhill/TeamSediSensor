#ifndef PS_FFAT_H_
#define PS_FFAT_H_

#include "Arduino.h"
#include "../Config/config.h"
#include "FS.h"
#include "FFat.h"
#include "testFile.h"

#define FILE_BUF_LEN 500

class PS_FFat {
    public: 
        static void init();
        static void readDataFile();
        static void setBuffer(char* p_newBuffer, size_t len);
        static void recvBuffer(uint8_t* p_destBuffer, size_t* len, size_t* offset);
        static void writeTestFile();
        static void getmd5Sum(char * output, const char * path);
        static void initializeFileBuffer(uint8_t* BLEfileBuffer, size_t* BLEfileBufferLen);
    private:
        static void readFile(fs::FS &fs, const char * path);
        static void writeFile(fs::FS &fs, const char * path, const char * message);
        static void appendFile(fs::FS &fs, const char * path, const char * message);
        static char p_fileBuffer[FILE_BUF_LEN];
        static size_t fileBufferLen;
};
#endif /* PS_FFAT_H_ */

