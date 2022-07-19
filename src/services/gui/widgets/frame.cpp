#include "frame.h"

#include "common.h"
#include "services/gui/gui.h"

void frame_draw_callback(Display *display, Widget *widget)
{
    assert_ptr(display);
    assert_ptr(widget);

    FrameModel *model = (FrameModel *) widget->context;

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

Frame *frame_alloc(uint8_t rows, uint8_t columns)
{
    Frame *frame = (Frame *) pvPortMalloc(sizeof(Frame));

    frame->widget = widget_alloc();
    widget_set_draw_callback(frame->widget, frame_draw_callback);

    frame->model = (FrameModel *) pvPortMalloc(sizeof(FrameModel));
    widget_set_context(frame->widget, frame->model);
    frame->model->rows = rows;
    frame->model->columns = columns;

    frame->model->widgets = (Widget ***) pvPortMalloc(rows * sizeof(Widget **));
    for (uint8_t i = 0; i < rows; i++)
    {
        frame->model->widgets[i] = (Widget **) pvPortMalloc(columns * sizeof(Widget *));
    }

    return frame;
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

void frame_place_widget(Frame *frame, Widget *widget, uint8_t row, uint8_t column)
{
    assert_ptr(frame);
    assert_ptr(widget);

    /*
    widget->width = frame->widget->width / frame->model->columns;
    widget->x = frame->widget->x + column * widget->width;
    widget->height = frame->widget->height / frame->model->rows;
    widget->y = frame->widget->y + row * widget->height;
    */

    widget->width = relative_block_length(frame->widget->width, frame->model->columns, column);
    widget->x = frame->widget->x + relative_block_start(frame->widget->width, frame->model->columns, column);
    widget->height = relative_block_length(frame->widget->height, frame->model->rows, row);
    widget->y = frame->widget->y + relative_block_start(frame->widget->height, frame->model->rows, row);

    frame->model->widgets[row][column] = widget;
}

void frame_grid(Frame *frame, Frame *parent_frame, uint8_t row, uint8_t column)
{
    assert_ptr(frame);
    assert_ptr(parent_frame);
    frame_place_widget(parent_frame, frame->widget, row, column);
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
