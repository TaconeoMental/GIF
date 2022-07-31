#ifndef WIDGET_LABEL
#define WIDGET_LABEL

#include "widget.h"
#include "frame.h"

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

void label_init(Label *label, const char *text);
void label_set_border(Label *label, bool b);
void label_grid(Label *label, Frame *frame, uint8_t column, uint8_t row, uint8_t x_p, uint8_t y_p);
void label_stack(Label *label, Frame *frame, FrameStackDirection stack_dir, int8_t width, int8_t height);

#endif
