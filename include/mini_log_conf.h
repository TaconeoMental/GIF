#ifndef MINI_LOG_CONF_H
#define MINI_LOG_CONF_H

#include <Arduino.h>

#define LOGGER_VERBOSITY_LEVEL LoggerVLevelTrace
#define LOGGER_USE_COLOUR
#define SERIAL_BAUD 9600
#define LOGGER_F_FUNC Serial.printf

#define LOGGER_INIT() \
    do { \
        if (LOGGER_VERBOSITY_LEVEL != LoggerVLevelOff) { \
            Serial.begin(SERIAL_BAUD); \
            vTaskDelay(pdMS_TO_TICKS(500));} \
    } while (0)

#endif
