#ifndef GUI_FRAME_H
#define GUI_FRAME_H

#include "widget.h"

struct Frame
{
    Widget *widget;

    uint8_t rows;
    uint8_t columns;
    Widget ***widgets;
};

Frame *frame_alloc(uint8_t rows, uint8_t columns);
void frame_grid(Frame *frame, Frame *parent_frame, uint8_t row, uint8_t column);
void frame_render(Frame *frame, Display *display);

#endif
