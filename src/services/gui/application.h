#ifndef GUI_APPLICATION_H
#define GUI_APPLICATION_H

#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>

//#include "gui.h"
#include "widgets/frame.h"

// Dependencias circulares? Perdón, no las conozco B)
struct Gui;

struct OgfApplication
{
    Gui *gui;
    Frame *current_frame;
    QueueHandle_t event_queue;
    void *context;
};

OgfApplication *ogf_application_alloc();
void ogf_application_set_context(OgfApplication *app, void *context);
void ogf_application_set_frame(OgfApplication *app, Frame *frame);
void ogf_application_start(OgfApplication *app);
void ogf_application_attach_to_gui(OgfApplication *app);
void ogf_application_request_draw(OgfApplication *app);

#endif
