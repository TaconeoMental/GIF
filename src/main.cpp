#include <Arduino.h>

#include "mini_log.h"
#include "services.h"

void setup()
{
    LOGGER_INIT();
    delay(1000);
    services_start();
}

void loop() {}
