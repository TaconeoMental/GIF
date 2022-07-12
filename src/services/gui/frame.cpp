#include "frame.h"

Frame *frame_alloc(uint8_t rows, uint8_t columns)
{
    Frame *frame = (Frame *) pvPortMalloc(sizeof(Frame));
    frame->widget = widget_alloc(frame);
    frame->rows = rows;
    frame->columns = columns;

    frame->widgets = (Widget ***) pvPortMalloc(columns * sizeof(Widget **));
    for (int i = 0; i < columns; i++)
    {
        frame->widgets[i] = (Widget **) pvPortMalloc(rows * sizeof(Widget *));
    }
}

void frame_grid(Frame *frame, Frame *parent_frame, uint8_t row, uint8_t column)
{

}

void frame_render(Frame *frame, Display *display)
{

}
