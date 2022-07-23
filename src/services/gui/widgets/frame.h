#ifndef GUI_FRAME_H
#define GUI_FRAME_H

#include "widget.h"

enum FrameType
{
    FRAME_TYPE_GRID,
    FRAME_TYPE_STACK
};

struct FrameGridModel
{
    bool has_border;
    uint8_t rows;
    uint8_t columns;
    Widget ***widgets;
};

struct FrameStackModel
{

};

struct Frame
{
    Widget *widget;
    FrameType frame_type;

    FrameGridModel *grid_model;
    FrameStackModel *stack_model;
};

Frame *frame_alloc();
void frame_set_border(Frame *frame, bool b);
bool frame_has_border(Frame *frame);
void frame_init_grid(Frame *frame, uint8_t columns, uint8_t rows);
void frame_grid(Frame *frame, Frame *parent_frame, uint8_t column, uint8_t row, uint8_t x_p, uint8_t y_p);
void frame_place_widget(Frame *frame, Widget *widget, uint8_t column, uint8_t row, uint8_t x_p, uint8_t y_p);
void frame_set_as_main(Frame *frame);

// DEBUG
void frame_print_info(Frame *frame);

#endif
