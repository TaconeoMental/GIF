#ifndef GUI_APPLICATION_H
#define GUI_APPLICATION_H

#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include "widgets/frame.h"
#include "services/input/input.h"
#include "services/gui/indexed_view.h"
#include "services/gui/view.h"

enum GifApplicationEventType
{
    GifApplicationEventTypeInput,
    GifApplicationEventTypeCustom
};

struct GifApplicationEvent
{
    GifApplicationEventType type;
    union
    {
        InputKey key;
        uint16_t custom_event;
    } data;
};

// Dependencias circulares? Perdón, no las conozco B)
struct Gui;

struct GifApplication
{
    Gui *gui;
    QueueHandle_t event_queue;
    void *context;
    IndexedViews *indexed_views;
};

GifApplication *gif_application_alloc();
void gif_application_start(GifApplication *app);
void gif_application_set_context(GifApplication *app, void *context);
void gif_application_attach_to_gui(GifApplication *app);
void gif_application_request_draw(GifApplication *app);
void gif_application_send_custom_event(GifApplication *app, uint8_t event);

// View
void gif_application_add_view(GifApplication *app, uint8_t view_id, GifApplicationView *view);
void gif_application_set_view(GifApplication *app, uint8_t view_id);
void gif_application_next_view(GifApplication *app, uint8_t view_id);

#endif
