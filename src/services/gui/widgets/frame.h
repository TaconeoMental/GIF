#ifndef GUI_FRAME_H
#define GUI_FRAME_H

#include "widget.h"
#include "services/gui/display.h"

#define INITIAL_STACK_SIZE 10

#define FRAME_STACK_FILL_X -1
#define FRAME_STACK_FILL_Y -2

enum FrameStackDirection
{
    FRAME_STACK_LEFT,
    FRAME_STACK_UP,
    FRAME_STACK_RIGHT,
    FRAME_STACK_DOWN
};

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
    bool has_border;
    Widget **widgets;
    uint8_t widget_count;
    uint8_t widget_arr_size;

    // Espacio disponible
    DisplayFrame available_frame;
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
void frame_set_as_main(Frame *frame);

// Funciones para tipo Grid
void frame_init_grid(Frame *frame, uint8_t columns, uint8_t rows);
void frame_grid(Frame *frame, Frame *parent_frame, uint8_t column, uint8_t row, uint8_t x_p, uint8_t y_p);
void frame_grid_widget(Frame *frame, Widget *widget, uint8_t column, uint8_t row, uint8_t x_p, uint8_t y_p);

// Funciones para tipo Stack
void frame_stack(Frame *frame, Frame *parent_frame, FrameStackDirection stack_dir, int8_t width, int8_t height);
void frame_stack_widget(Frame *frame, Widget *widget, FrameStackDirection stack_dir, int8_t width, int8_t height);

// DEBUG
void frame_print_info(Frame *frame);

#endif
