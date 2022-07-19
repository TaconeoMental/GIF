#ifndef WIDGET_LABEL
#define WIDGET_LABEL

#include "widget.h"
#include "frame.h"

#define MAX_LABEL_TEXT_LENGTH 20

struct LabelModel
{
    char *text;
    bool has_border;
    uint8_t x_padding;
    uint8_t y_padding;
};

struct Label
{
    Widget *widget;
    LabelModel *model;
};

void label_init(Label *label, char *text);
void label_grid(Label *label, Frame *frame, uint8_t row, uint8_t column);
void label_set_padding(Label *label, uint8_t x_p, uint8_t y_p);
void label_has_border(Label *label, bool b);
#endif
