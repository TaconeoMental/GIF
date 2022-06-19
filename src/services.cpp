#include "services.h"

#include "mini_log.h"

// Servicios
extern void input_service(void *p);
extern void gui_service(void *p);

// Aplicaciones
extern void test_app_service(void *p);

const GuiService GuiServices[] =
{
    {input_service, "InputService", 2048, 1},
    {gui_service, "GuiService", 2048, 1}
};

// Primera aplicación siempre es la primera en ejecutarse
const GuiService GuiApplications[] =
{
    {test_app_service, "Test App", 2048, 1}
};

const uint8_t OGF_SERVICE_COUNT = sizeof(GuiServices) / sizeof(GuiService);
const uint8_t OGF_APPLICATION_COUNT = sizeof(GuiApplications) / sizeof(GuiService);


void gui_service_start(const GuiService *service)
{
        xTaskCreate(service->callback,
                    service->name,
                    service->stack_depth,
                    NULL,
                    service->priority,
                    NULL);
}

void services_start()
{
    MLOG_I("Starting services");

    GuiService service;
    for (uint8_t i = 0; i < OGF_SERVICE_COUNT; ++i)
    {
        service = GuiServices[i];

        MLOG_I("Starting '%s' task. SD: %d. Priority: %d",
               service.name,
               service.stack_depth,
               service.priority);

        gui_service_start(&service);
    }
    vTaskDelay(pdMS_TO_TICKS(500));
    gui_service_start(&GuiApplications[0]);
    MLOG_I("Services started succesfully");
}
