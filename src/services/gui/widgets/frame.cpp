#include "frame.h"

#include "common.h"
#include "services/gui/gui.h"

// Init de cada FrameType
static FrameStackModel *frame_stack_model_alloc()
{
    FrameStackModel *model = (FrameStackModel *) pvPortMalloc(sizeof(FrameStackModel));
    model->has_border = false;
    model->widget_count = 0;
    model->widget_arr_size = INITIAL_STACK_SIZE;
    model->widgets = (Widget **) pvPortMalloc(INITIAL_STACK_SIZE * sizeof(Widget *));
    model->available_frame = {0, 0, GUI_DISPLAY_WIDTH, GUI_DISPLAY_HEIGHT};
    return model;
}

static FrameGridModel *frame_grid_model_alloc(uint8_t columns, uint8_t rows)
{
    FrameGridModel *model = (FrameGridModel *) pvPortMalloc(sizeof(FrameGridModel));
    model->has_border = false;
    model->columns = columns;
    model->rows = rows;
    model->widgets = (Widget ***) pvPortMalloc(rows * sizeof(Widget **));
    for (uint8_t i = 0; i < rows; i++)
    {
        model->widgets[i] = (Widget **) pvPortMalloc(columns * sizeof(Widget *));
    }
    return model;
}


// Callbacks de dibujo de cada FrameType
void frame_grid_draw_callback(Display *display, Widget *widget)
{
    assert_ptr(display);
    assert_ptr(widget);

    FrameGridModel *model = (FrameGridModel *) widget->context;

    if (model->has_border)
    {
        display_draw_frame(display, widget->x,
                                    widget->y,
                                    widget->width,
                                    widget->height);
    }

    Widget *curr_widget;
    for (uint8_t r = 0; r < model->rows; r++)
    {
        for (uint8_t c = 0; c < model->columns; c++)
        {
            curr_widget = model->widgets[r][c];
            curr_widget->draw_callback(display, curr_widget);
        }
    }
}

void frame_stack_draw_callback(Display *display, Widget *widget)
{
    assert_ptr(display);
    assert_ptr(widget);

    FrameStackModel *model = (FrameStackModel *) widget->context;

    if (model->has_border)
    {
        display_draw_frame(display, widget->x,
                                    widget->y,
                                    widget->width,
                                    widget->height);
    }

    Widget *curr_widget;
    for (uint8_t i = 0; i < model->widget_count; i++)
    {
        curr_widget = model->widgets[i];
        curr_widget->draw_callback(display, curr_widget);
    }
}

Frame *frame_alloc()
{
    Frame *frame = (Frame *) pvPortMalloc(sizeof(Frame));
    frame->frame_type = FRAME_TYPE_STACK;
    frame->widget = widget_alloc();
    frame->stack_model = frame_stack_model_alloc();
    widget_set_context(frame->widget, frame->stack_model);
    widget_set_draw_callback(frame->widget, frame_stack_draw_callback);
    return frame;
}

void frame_set_border(Frame *frame, bool b)
{
    assert_ptr(frame);
    switch (frame->frame_type)
    {
        case FRAME_TYPE_GRID:
            frame->grid_model->has_border = true;
            break;
        case FRAME_TYPE_STACK:
            frame->stack_model->has_border = true;
    }
}

// static??
bool frame_has_border(Frame *frame)
{
    assert_ptr(frame);
    switch (frame->frame_type)
    {
        case FRAME_TYPE_GRID:
            return frame->grid_model->has_border;
        case FRAME_TYPE_STACK:
            return frame->stack_model->has_border;
    }
    return false;
}

void frame_init_grid(Frame *frame, uint8_t columns, uint8_t rows)
{
    assert_ptr(frame);
    frame->frame_type = FRAME_TYPE_GRID;
    frame->grid_model = frame_grid_model_alloc(columns, rows);
    widget_set_context(frame->widget, frame->grid_model);
    widget_set_draw_callback(frame->widget, frame_grid_draw_callback);
}

// Porfa no pregunten por este algoritmo, me costó caleta xd
static uint8_t relative_block_length(int total, int divisions, int index)
{
    uint8_t x;
    uint8_t def = total / divisions;
    uint8_t resto = total % divisions;
    if (resto == 0) return def;
    if (index == divisions / 2 && resto % 2 != 0) return def + 1;
    for (uint8_t i = 0; i < resto / 2; i++)
    {
        x = i * divisions / (resto - 1);
        if (index == x || index == divisions - x - 1)
        {
            def++;
            break;
        }
    }
    return def;
}

static uint8_t relative_block_start(int total, int divisions, int index)
{
    uint8_t final_index = 0;
    for (uint8_t i = 0; i < index; i++)
    {
        final_index += relative_block_length(total, divisions, i);
    }
    return final_index;
}

void frame_grid_widget(Frame *frame, Widget *widget, uint8_t column, uint8_t row, uint8_t x_p, uint8_t y_p)
{
    assert_ptr(frame);
    assert_ptr(widget);
    assert_c(frame->frame_type == FRAME_TYPE_GRID);

    uint8_t border_pixel = 0;
    if (frame_has_border(frame)) border_pixel = 1;

    widget->width = relative_block_length(frame->widget->width - 2 * border_pixel, frame->grid_model->columns, column) - 2 * x_p;
    widget->x = frame->widget->x + x_p + border_pixel
                + relative_block_start(frame->widget->width - 2 * border_pixel, frame->grid_model->columns, column);
    widget->height = relative_block_length(frame->widget->height - 2 * border_pixel, frame->grid_model->rows, row) - 2 * y_p;
    widget->y = frame->widget->y + y_p + border_pixel
                + relative_block_start(frame->widget->height - 2 * border_pixel, frame->grid_model->rows, row);

    frame->grid_model->widgets[row][column] = widget;
}

void frame_grid(Frame *frame, Frame *parent_frame, uint8_t column, uint8_t row, uint8_t x_p, uint8_t y_p)
{
    assert_ptr(frame);
    assert_ptr(parent_frame);
    assert_c(parent_frame->frame_type == FRAME_TYPE_GRID);
    frame_grid_widget(parent_frame, frame->widget, column, row, x_p, y_p);
}

void frame_stack_widget(Frame *frame, Widget *widget, FrameStackDirection stack_dir, int8_t width, int8_t height)
{
    assert_ptr(frame);
    assert_ptr(widget);
    assert_c(frame->frame_type == FRAME_TYPE_STACK);
    assert_c(width == FRAME_STACK_FILL_X || height == FRAME_STACK_FILL_Y);

    DisplayFrame *available_frame = &frame->stack_model->available_frame;
    uint8_t x_coor = available_frame->x;
    uint8_t y_coor = available_frame->y;
    if (width == FRAME_STACK_FILL_X || width > available_frame->width) width = available_frame->width;
    if (height == FRAME_STACK_FILL_Y || height > available_frame->height) height = available_frame->height;
    switch (stack_dir)
    {
        case FRAME_STACK_LEFT:
            available_frame->x += width;
            available_frame->width -= width;
            break;
        case FRAME_STACK_UP:
            available_frame->y += height;
            available_frame->height -= height;
            break;
        case FRAME_STACK_RIGHT:
            x_coor = available_frame->width - width;
            available_frame->width -= width;
            break;
        case FRAME_STACK_DOWN:
            y_coor = available_frame->height - height;
            available_frame->height -= height;
            break;
    }
    widget->x = x_coor;
    widget->y = y_coor;
    widget->width = width;
    widget->height = height;

    FrameStackModel *model = frame->stack_model;
    if (model->widget_count == model->widget_arr_size)
    {
        model->widget_arr_size += 10; // Completa y totalmente arbitrario B)
        //model->widgets = (Widget *) pvPortReAlloc(model->widgets, model->widget_arr_size);
    }
    model->widgets[model->widget_count++] = widget;
}

void frame_stack(Frame *frame, Frame *parent_frame, FrameStackDirection stack_dir, int8_t width, int8_t height)
{
    assert_ptr(frame);
    assert_ptr(parent_frame);
    assert_c(parent_frame->frame_type == FRAME_TYPE_STACK);
    frame_stack_widget(parent_frame, frame->widget, stack_dir, width, height);
}

void frame_print_info(Frame *frame)
{
    MLOG_W("P(%d, %d, %d, %d)", frame->widget->x, frame->widget->y, frame->widget->width, frame->widget->height);
}

void frame_set_as_main(Frame *frame)
{
    assert_ptr(frame);
    frame->widget->width = GUI_DISPLAY_WIDTH;
    frame->widget->height = GUI_DISPLAY_HEIGHT;
    frame->widget->x = 0;
    frame->widget->y = 0;
}
