#ifndef DECODE_LOGIC_H
#define DECODE_LOGIC__H

#include "stm32f1xx_hal.h"  // Include the necessary STM32 HAL library headers

typedef struct {
    // Define your data structure to hold decoded information
    int wire_connected;
    int battery_charging;
    int battery_low;
    int battery_ready;
    int soc;
    float battery_current;
    float battery_voltage;
    const char *battery_failure;
} DecodedMessage;

void decodeMessage(const uint8_t *rxData, DecodedMessage *decodedMessage);

#endif // DECODE_H