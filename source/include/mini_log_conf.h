#ifndef MINI_LOG_CONF_H
#define MINI_LOG_CONF_H

#include <Arduino.h>

#define LOGGER_VERBOSITY_LEVEL LoggerVLevelOff
#define LOGGER_USE_COLOUR
#define SERIAL_BAUD 9600
#define LOGGER_F_FUNC printf

#define LOGGER_INIT() \
    do { \
        if (LOGGER_VERBOSITY_LEVEL != LoggerVLevelOff) { \
            Serial.begin(SERIAL_BAUD); \
            vTaskDelay(pdMS_TO_TICKS(1000));} \
    } while (0)

#endif
