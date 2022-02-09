#include "PS_FileXferService.h"

/* static */ BLEService* PS_FileXferService::p_fileXferService = NULL;

void PS_FileXferService::createService(BLEServer* p_BLE_Server){
    /* Create the BLE Service */
    p_fileXferService = p_BLE_Server->createService(SERVICE_UUID);
    /* Create Characteristics */
    PS_FileXferReadChar::createCharacteristic(p_fileXferService);
    /* Start the service */
    p_fileXferService->start();
}

/* static */ BLECharacteristic* PS_FileXferReadChar::p_readChar = NULL;
/* static */ volatile PS_FileXferReadChar::XferStatus PS_FileXferReadChar::fileXferStatus = PAUSED;
/* static */ uint8_t PS_FileXferReadChar::p_xferBuffer[BLE_MSG_LEN] = {0};
/* static */ size_t PS_FileXferReadChar::xferBufferLen = 0;
/* static */ size_t PS_FileXferReadChar::offset = 0;
/* static */ size_t PS_FileXferReadChar::fileSize = 0;

/* static */ void PS_FileXferReadChar::createCharacteristic(BLEService* p_service){
    /* creat the Characteristic */
    p_readChar = p_service->createCharacteristic(READ_CHAR_UUID, 
                                                 BLECharacteristic::PROPERTY_READ     |
                                                 BLECharacteristic::PROPERTY_INDICATE
                                                );
    /* Set callbacks for charactersitic behavior */
    p_readChar->setCallbacks(new characteristicCallbacks());
    /* Create descriptor -> so we can indicate to the connected device when data is ready */
    BLE2902* desc2902 = new BLE2902();
    /* set callbacks to handle descriptor behavior on events */
    desc2902->setCallbacks(new descCallbacks());
    p_readChar->addDescriptor(desc2902);
}

void PS_FileXferReadChar::characteristicCallbacks::onStatus(BLECharacteristic* p_characteristic, Status s, uint32_t code){
    /* This callback is called when status updates happen 
     * Hook into behaviour for when Indicate returned successfully
     * to continue transfer
     * if failed reset to beginning
     */
    switch(s) {
        case SUCCESS_INDICATE:
            if(fileSize == offset)
                fileXferStatus = FINISHED;
            else
                fileXferStatus = SEND_MSG; 
            break;
        /* intentionally letting things fall through here */
	    case ERROR_INDICATE_DISABLED:
	    case ERROR_NOTIFY_DISABLED:
	    case ERROR_GATT:
        case ERROR_NO_CLIENT:
        case ERROR_INDICATE_TIMEOUT:
        case ERROR_INDICATE_FAILURE:
            fileXferStatus = FAILED;
            break;
        default: 
            break;
    }
}

/* This callback is called whenever the descriptor is writen
 *   when Linux requests notifications/indications it writes to the descriptor
 *   (only verified for Linux)
 *   Problem: Linux drivers write the last value it had stored as the descriptor
 *      Hence, if it did have request notifications on last time it was on 
 *      when the device connects again it will start transferring all the file on 
 *      connecting, This can't be solved here b/c the device is requesting indications
 *      based on what it's telling this device But write follow-up integration tests of 
 *      what happens if linux formally requests notifications part of the way thought the transmission
 *   Hence start sending indications on this act 
 */
void PS_FileXferReadChar::descCallbacks::onWrite(BLEDescriptor* p_descriptor){
    uint8_t len = p_descriptor->getLength();
    uint8_t* val = p_descriptor->getValue();
    for(uint8_t i = 0; i < len; i++) {
        Serial.printf("%02x", val[i]);
    }
    Serial.print("\r\n");
    if(((BLE2902*)p_descriptor)->getIndications())
        fileXferStatus = STARTING;
}

/* run when new device connects to server 
 * should initialize the buffer 
 *     first message gives checksum and total size
 *     to help configure the receiver and verify transfer
 */
/* static */ void PS_FileXferReadChar::onConnect(){
    fileXferStatus = PAUSED;
    PS_SDFile::initializeFileBuffer(p_xferBuffer, &xferBufferLen); 
    p_readChar->setValue(p_xferBuffer, xferBufferLen);
    fileSize = 0;
    offset = 0;
}

/* Called periodically while device is connected 
 * take appropriate action based on the status of the transfer
 */
/* static */ void PS_FileXferReadChar::whileConnect(){
    switch(fileXferStatus) {
        case PAUSED:
            break;
        case STARTING:
            fileXferStatus = WAIT_RESP;
            PS_SDFile::initializeFileBuffer(p_xferBuffer, &xferBufferLen); 
            p_readChar->setValue(p_xferBuffer, xferBufferLen);
            Serial.println("--------------------Starting FileXfer--------------------");
            /* TODO: convert this into using the File header struct to get data out */
            Serial.printf("File Header:\r\n\t%s, Filesize: ", p_xferBuffer);
            fileSize = p_xferBuffer[16] + (p_xferBuffer[17] << 8);
            p_readChar->indicate();
            Serial.println(fileSize);
            break;
        case SEND_MSG:
            fileXferStatus = WAIT_RESP;
            /* TODO: Find out if the MTUs are being set correctly 
             *  Max length specified as 20 bytes
             *  If this works (on more than just linux) leave it
             *  otherwise can switch to a 20 bytes max or 
             *  configure state machine to indicate new data and client reads
             */
            xferBufferLen = BLE_MSG_LEN;
            PS_SDFile::recvBuffer(p_xferBuffer, &xferBufferLen, &offset);
            Serial.printf("Sending MSG\r\n\toffset: %d, full fileSize: %d, text: %s, len: %d\r\n", offset, fileSize, p_xferBuffer, xferBufferLen);
            p_readChar->setValue(p_xferBuffer, xferBufferLen);
            p_readChar->indicate();
            break;
        case WAIT_RESP:
            /* We will exit this case on the when indicate completes successfully */
            break;
        case FINISHED:
            Serial.println("--------------------File Xfer Finished--------------------");
            offset = 0;
            fileSize = 0;
            fileXferStatus = PAUSED;
            break;
        case FAILED:
            Serial.println("--------------------File Xfer FAILED--------------------");
            offset = 0;
            fileSize = 0;
            fileXferStatus = PAUSED;
            break;
        default:
            break;
    }
}

/* run when client disconnects 
 * resets file transfer parameters
 * should be redundant as this happens when 
 *     transfer terminates, either success or failure
 */
/* static */ void PS_FileXferReadChar::onDisconnect(){
    offset = 0;
    fileSize = 0;
    fileXferStatus = PAUSED;
}
