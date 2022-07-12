#include "label.h"

void label_init(Label *label, char *text)
{
    label->widget = widget_alloc(label);

    label->has_border = true;

    label->text = (char *) pvPortMalloc(MAX_LABEL_TEXT_LENGTH + 1);
    strncpy(label->text, text, MAX_LABEL_TEXT_LENGTH + 1);
}

void label_grid(Label *label, Frame *frame, uint8_t row, uint8_t column)
{

}

void label_draw_callback(Display *display, Widget *widget)
{
    Label *label = (Label *) widget->context;

    display_draw_frame(display, widget->x,
                                widget->y,
                                widget->width,
                                widget->height);
}
