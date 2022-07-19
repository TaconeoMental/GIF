#include "label.h"

#include "common.h"

void label_draw_callback(Display *display, Widget *widget)
{
    assert_ptr(display);
    assert_ptr(widget);

    LabelModel *label = (LabelModel *) widget->context;

    if (label->has_border)
    {
        display_draw_frame(display, widget->x + label->x_padding,
                                    widget->y + label->y_padding,
                                    widget->width - 2 * label->x_padding,
                                    widget->height - 2 * label->y_padding);
    }

    // TODO: Verificar que el tamaño del widget no sea mayor al frame actual.
    // Si es así, que el widget ocupe el máximo posible.
    DisplayFrame display_frame = display_get_frame(display);

    // TODO: Esta parte no me gusta
    DisplayFrame widget_frame = {widget->x, widget->y, widget->width, widget->height};
    display_set_frame(display, widget_frame);

    display_draw_str_aligned(display, label->text, AlignmentCenter, AlignmentCenter);

    // Reseteamos el frame
    display_set_frame(display, display_frame);
}

void label_init(Label *label, char *text)
{
    label->widget = widget_alloc();
    widget_set_draw_callback(label->widget, label_draw_callback);

    LabelModel *model = (LabelModel *) pvPortMalloc(sizeof(LabelModel));
    model->has_border = false;
    model->x_padding = 0;
    model->y_padding = 0;
    model->text = (char *) pvPortMalloc(MAX_LABEL_TEXT_LENGTH + 1);
    strncpy(model->text, text, MAX_LABEL_TEXT_LENGTH + 1);

    label->model = model;
    widget_set_context(label->widget, model);
}

void label_grid(Label *label, Frame *frame, uint8_t row, uint8_t column)
{
    assert_ptr(label);
    assert_ptr(frame);
    frame_place_widget(frame, label->widget, row, column);
}

void label_set_padding(Label *label, uint8_t x_p, uint8_t y_p)
{
    assert_ptr(label);
    label->model->x_padding = x_p;
    label->model->y_padding = y_p;
}

void label_has_border(Label *label, bool b)
{
    assert_ptr(label);
    label->model->has_border = b;
}
