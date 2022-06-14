#ifndef OGF_SERVICES
#define OGF_SERVICES

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

struct GuiService
{
    void (*init_function)(void);
    TaskFunction_t callback;
    char *name;
    uint16_t stack_depth;
    uint8_t priority;
};

extern const GuiService GuiServices[];
extern const uint8_t OGF_SERVICE_COUNT;

void services_start();

#endif
