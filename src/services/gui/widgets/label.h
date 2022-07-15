#ifndef WIDGET_LABEL
#define WIDGET_LABEL

#include "services/gui/widget.h"
#include "services/gui/frame.h"

#define MAX_LABEL_TEXT_LENGTH 20

struct LabelModel
{
    char *text;
    bool has_border;
};

struct Label
{
    Widget *widget;
    LabelModel *model;
};

void label_init(Label *label, char *text);
void label_grid(Label *label, Frame *frame, uint8_t row, uint8_t column);
#endif
