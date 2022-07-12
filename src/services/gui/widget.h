#ifndef GUI_WIDGET_H
#define GUI_WIDGET_H

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

Widget *widget_alloc(void *context);

#endif
