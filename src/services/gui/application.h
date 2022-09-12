#ifndef GUI_APPLICATION_H
#define GUI_APPLICATION_H

#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include "widgets/frame.h"
#include "services/input/input.h"
#include "services/gui/indexed_view.h"
#include "services/gui/view.h"

enum OgfApplicationEventType
{
    OgfApplicationEventTypeInput,
    OgfApplicationEventTypeCustom
};

struct OgfApplicationEvent
{
    OgfApplicationEventType type;
    union
    {
        InputKey key;
        uint16_t custom_event;
    } data;
};

// Dependencias circulares? Perdón, no las conozco B)
struct Gui;

struct OgfApplication
{
    Gui *gui;
    QueueHandle_t event_queue;
    void *context;
    IndexedViews *indexed_views;
};

OgfApplication *ogf_application_alloc();
void ogf_application_start(OgfApplication *app);
void ogf_application_set_context(OgfApplication *app, void *context);
void ogf_application_attach_to_gui(OgfApplication *app);
void ogf_application_request_draw(OgfApplication *app);
void ogf_application_send_custom_event(OgfApplication *app, uint8_t event);

// View
void ogf_application_add_view(OgfApplication *app, uint8_t view_id, OgfApplicationView *view);
void ogf_application_set_view(OgfApplication *app, uint8_t view_id);
void ogf_application_next_view(OgfApplication *app, uint8_t view_id);

#endif
