#include "frame.h"

#include "common.h"
#include "services/gui/gui.h"

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

Frame *frame_alloc()
{
    Frame *frame = (Frame *) pvPortMalloc(sizeof(Frame));
    frame->frame_type = FRAME_TYPE_STACK;

    frame->widget = widget_alloc();
    widget_set_draw_callback(frame->widget, frame_grid_draw_callback);

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
    }
    return false;
}

void frame_init_grid(Frame *frame, uint8_t columns, uint8_t rows)
{
    assert_ptr(frame);
    frame->frame_type = FRAME_TYPE_GRID;
    frame->grid_model = (FrameGridModel *) pvPortMalloc(sizeof(FrameGridModel));
    widget_set_context(frame->widget, frame->grid_model);
    frame->grid_model->rows = rows;
    frame->grid_model->columns = columns;
    frame->grid_model->has_border = false;

    frame->grid_model->widgets = (Widget ***) pvPortMalloc(rows * sizeof(Widget **));
    for (uint8_t i = 0; i < rows; i++)
    {
        frame->grid_model->widgets[i] = (Widget **) pvPortMalloc(columns * sizeof(Widget *));
    }
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

void frame_place_widget(Frame *frame, Widget *widget, uint8_t column, uint8_t row, uint8_t x_p, uint8_t y_p)
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
    frame_place_widget(parent_frame, frame->widget, column, row, x_p, y_p);
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
