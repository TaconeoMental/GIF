#include "empty_widget.h"

#include "common.h"

void empty_widget_draw_callback(Display *display, Widget *widget)
{
    assert_ptr(display);
    assert_ptr(widget);
}

void empty_widget_init(EmptyWidget *e_widget)
{
    e_widget->widget = widget_alloc();
    widget_set_draw_callback(e_widget->widget, empty_widget_draw_callback);
}

void empty_widget_grid(EmptyWidget *e_widget, Frame *frame, uint8_t column, uint8_t row, uint8_t x_p, uint8_t y_p)
{
    assert_ptr(e_widget);
    assert_ptr(frame);
    frame_grid_widget(frame, e_widget->widget, column, row, x_p, y_p);
}

void empty_widget_stack(EmptyWidget *e_widget, Frame *frame, FrameStackDirection stack_dir, int8_t width, int8_t height)
{
    assert_ptr(e_widget);
    assert_ptr(frame);
    frame_stack_widget(frame, e_widget->widget, stack_dir, width, height);
}
