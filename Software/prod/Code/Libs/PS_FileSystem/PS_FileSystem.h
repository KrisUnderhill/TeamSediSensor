#ifndef PS_FILE_SYSTEM_H_
#define PS_FILE_SYSTEM_H_

#include "Arduino.h"
#include "../Config/config.h"
#include "FS.h"
#include "SD.h"
#include "SPI.h"
//#include "FFat.h"

class PS_FileSystem {
    public: 
        static void init();
        static File open(const char* path, int mode);
        static void getmd5Sum(char* output, const char* path);
        static void getmd5Sum(char* output, char* str, uint16_t len);
    private:
        static bool verifyFileSystem();
        static bool writeExpectedFile(int expectedFileIndex);

        static fs::FS fileSystem;
        static bool fsGood;
        static uint16_t fileLocks;
};
#endif /* PS_FILE_SYSTEM_H_ */

