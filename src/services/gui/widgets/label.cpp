#include "label.h"

#include "common.h"

void label_draw_callback(Display *display, Widget *widget)
{
    assert_ptr(display);
    assert_ptr(widget);


    uint8_t radius = 0.20 * widget->width;
    DisplayFrame display_frame = display_get_frame(display);
    LabelModel *label = (LabelModel *) widget->context;

    if (label->has_border)
    {
        if (label->has_round_border)
        {
            display_draw_rframe(display, widget->x,
                                         widget->y,
                                         widget->width,
                                         widget->height,
                                         radius);
        }
        else
        {
            display_draw_frame(display, widget->x,
                                         widget->y,
                                         widget->width,
                                         widget->height);
        }
    }
    else if (label->has_fill)
    {
        if (label->has_round_border)
        {
            display_draw_rbox(display, widget->x,
                                       widget->y,
                                       widget->width,
                                       widget->height,
                                       radius);
        }
        else
        {

            display_draw_box(display, widget->x,
                                      widget->y,
                                      widget->width,
                                      widget->height);
        }
    }

    DisplayFrame widget_frame = {widget->x,
                                 widget->y,
                                 MIN(widget->width, display_frame.width),
                                 MIN(widget->height, display_frame.height)};
    display_set_frame(display, widget_frame);
    if (label->has_fill) display_invert_colour(display);
    display_draw_str_aligned(display, label->text, AlignmentCenter, AlignmentCenter);
    if (label->has_fill) display_invert_colour(display);

    // Reseteamos el frame
    display_set_frame(display, display_frame);
}

void label_init(Label *label, const char *text)
{
    label->widget = widget_alloc();
    widget_set_draw_callback(label->widget, label_draw_callback);

    LabelModel *model = (LabelModel *) pvPortMalloc(sizeof(LabelModel));
    model->has_border = false;
    model->has_round_border = false;
    model->has_fill = false;

    // TODO: Generalizar esto con un macro o algo siono
    model->text = (char *) pvPortMalloc(MAX_LABEL_TEXT_LENGTH + 1);
    strncpy(model->text, text, MAX_LABEL_TEXT_LENGTH + 1);

    label->model = model;
    widget_set_context(label->widget, model);
}

// Setters
void label_set_border(Label *label, bool b)
{
    assert_ptr(label);
    label->model->has_border = b;
}

void label_set_round_border(Label *label, bool b)
{
    assert_ptr(label);
    label->model->has_round_border = b;
}

void label_set_fill(Label *label, bool b)
{
    assert_ptr(label);
    label->model->has_fill = b;
}

// Posicionamiento
void label_grid(Label *label, Frame *frame, uint8_t column, uint8_t row, uint8_t x_p, uint8_t y_p)
{
    assert_ptr(label);
    assert_ptr(frame);
    frame_grid_widget(frame, label->widget, column, row, x_p, y_p);
}

void label_stack(Label *label, Frame *frame, FrameStackDirection stack_dir, int8_t width, int8_t height)
{
    assert_ptr(label);
    assert_ptr(frame);
    frame_stack_widget(frame, label->widget, stack_dir, width, height);
}
