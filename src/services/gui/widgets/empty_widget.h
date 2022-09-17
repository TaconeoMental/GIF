#ifndef WIDGET_EMPTY
#define WIDGET_EMPTY

#include "widget.h"
#include "frame.h"
#include "services/gui/display.h"

struct EmptyWidget
{
    Widget *widget;
};

void empty_widget_init(EmptyWidget *e_widget);

void empty_widget_grid(EmptyWidget *e_widget, Frame *frame, uint8_t column, uint8_t row, uint8_t x_p, uint8_t y_p);
void empty_widget_stack(EmptyWidget *e_widget, Frame *frame, FrameStackDirection stack_dir, int8_t width, int8_t height);

#endif
