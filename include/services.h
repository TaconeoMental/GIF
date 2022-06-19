#ifndef OGF_SERVICES
#define OGF_SERVICES

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

struct GuiService
{
    TaskFunction_t callback;
    char *name;
    uint16_t stack_depth;
    uint8_t priority;
};

void gui_service_start(const GuiService *service);

extern const GuiService GuiServices[];
extern const uint8_t OGF_SERVICE_COUNT;

extern const GuiService GuiApplications[];
extern const uint8_t OGF_APPLICATION_COUNT;

void services_start();

#endif
