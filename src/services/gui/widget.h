#ifndef GUI_WIDGET_H
#define GUI_WIDGET_H

#include <stdint.h>
#include "display.h"

// FD pq soy un desordenado
struct Widget;

typedef void (*WidgetDrawCallback)(Display *display, Widget *widget);

struct Widget
{
    uint8_t x;
    uint8_t y;
    uint8_t width;
    uint8_t height;

    WidgetDrawCallback draw_callback;

    void *context;
};

Widget *widget_alloc();
void widget_set_draw_callback(Widget *widget, WidgetDrawCallback callback);
void widget_set_context(Widget *widget, void *context);

#endif
