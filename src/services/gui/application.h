#ifndef GUI_APPLICATION_H
#define GUI_APPLICATION_H

#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>

#include "widgets/frame.h"

struct OgfApplication
{
    Frame *current_frame;
    QueueHandle_t event_queue;
    void *context;
};

OgfApplication *ogf_application_alloc();
void ogf_application_set_context(OgfApplication *app, void *context);
void ogf_application_set_frame(OgfApplication *app, Frame *frame);
void ogf_application_start(OgfApplication *app);
void ogf_application_draw(OgfApplication *app);

#endif
