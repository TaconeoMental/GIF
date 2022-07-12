#include <Arduino.h>

#include "mini_log.h"
#include "services.h"

void setup()
{
    LOGGER_INIT();
    services_start();
}

void loop() {}
