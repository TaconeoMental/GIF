#ifndef GUI_FRAME_H
#define GUI_FRAME_H

#include "widget.h"

struct FrameModel
{
    uint8_t rows;
    uint8_t columns;
    Widget ***widgets;
};

struct Frame
{
    Widget *widget;
    FrameModel *model;
};

Frame *frame_alloc(uint8_t rows, uint8_t columns);
void frame_grid(Frame *frame, Frame *parent_frame, uint8_t row, uint8_t column);
void frame_place_widget(Frame *frame, Widget *widget, uint8_t row, uint8_t column);
void frame_set_as_main(Frame *frame);

// DEBUG
void frame_print_info(Frame *frame);

#endif
