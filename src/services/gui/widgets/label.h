#ifndef WIDGET_LABEL
#define WIDGET_LABEL

#include "services/gui/widget.h"

#define MAX_LABEL_TEXT_LENGTH 20

struct Label
{
    Widget *widget;
    char *text;
    bool has_border;
};

void label_init(Label *label, char *text);
void label_grid(Label *label, Frame *frame, uint8_t row, uint8_t column);
#endif
