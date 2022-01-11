#ifndef PS_FFAT_H_
#define PS_FFAT_H_

#include "Arduino.h"
#include "../Config/config.h"
#include "FS.h"
#include "FFat.h"

#define FILE_MSG_LEN 500

class PS_FFat {
    public: 
        static void init();
        static void setBuffer(uint8_t* p_newBuffer, size_t len);
        static void recvBuffer(uint8_t* p_destBuffer, size_t* len);
    private:
};
#endif /* PS_FFAT_H_ */

