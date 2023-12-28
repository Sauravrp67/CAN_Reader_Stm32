#include "decode_logic.h"
#include "main.h"

void decodeMessage(const uint8_t *rxData, DecodedMessage *decodedMessage) {

    //Set the flags to use them in while loop

    //Decode the first Byte
    decodedMessage->wire_connected = (rxData[0] & 0x01) ? 1 : 0; // 0x01 = 0000 0001
    decodedMessage->battery_charging = (rxData[0] & 0x02) ? 1 : 0; // 0x02 = 0000 0010
    decodedMessage->battery_low = (rxData[0] & 0x04) ? 1 : 0; // 0x04 = 0000 0100
    decodedMessage->battery_ready = (rxData[0] & 0x08) ? 1 : 0; // 0x08 = 0000 1000
    
    //Store 2nd byte on SOC variable
    decodedMessage->soc = rxData[1];
    //Decode the 3rd and 4th byte, and 5th and 6th byte to get the current and voltage
    decodedMessage->battery_current = (((rxData[3] << 8) | rxData[2]) - 5000) / 0.1;
    decodedMessage->battery_voltage = ((rxData[5] << 8) | rxData[4]) / 1000;

    //Decode the 7th byte to get the battery failure
    uint8_t battery_failure = rxData[6];
    switch (battery_failure) {
        case 0x00:
            decodedMessage->battery_failure = "No Failure";
            break;
        case 0x01:
            decodedMessage->battery_failure = "Level 1(Stop Now)";
            break;
        case 0x02:
            decodedMessage->battery_failure = "Level 2(Power Reduce to 50)";
            break;
        case 0x03:
            decodedMessage->battery_failure = "Level 3(Alarm)";
            break;
        default:
            decodedMessage->battery_failure = "Unknown";
            break;
    }


}