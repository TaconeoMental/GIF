#include "widget.h"

#include "common.h"

Widget *widget_alloc()
{
    Widget *widget = (Widget *) pvPortMalloc(sizeof(Widget));
    return widget;
}

void widget_set_draw_callback(Widget *widget, WidgetDrawCallback callback)
{
    assert_ptr(widget);
    widget->draw_callback = callback;
}

void widget_set_context(Widget *widget, void *context)
{
    assert_ptr(widget);
    assert_ptr(context);
    widget->context = context;
}

void widget_inherit_shape(Widget *child, Widget *parent)
{
    child->x = parent->x;
    child->y = parent->y;
    child->width = parent->width;
    child->height = parent->height;
}
