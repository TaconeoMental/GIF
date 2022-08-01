#ifndef WIDGET_LABEL
#define WIDGET_LABEL

#include "widget.h"
#include "frame.h"
#include "services/gui/display.h"

#define MAX_LABEL_TEXT_LENGTH 20

struct LabelModel
{
    char *text;
    bool has_border;
    bool has_round_border;
    bool has_fill;
};

struct Label
{
    Widget *widget;
    LabelModel *model;
};

void label_init(Label *label, const char *text);

// Setters
void label_set_border(Label *label, bool b);
void label_set_round_border(Label *label, bool b);
void label_set_fill(Label *label, bool b);

// Posicionamiento
void label_grid(Label *label, Frame *frame, uint8_t column, uint8_t row, uint8_t x_p, uint8_t y_p);
void label_stack(Label *label, Frame *frame, FrameStackDirection stack_dir, int8_t width, int8_t height);

#endif
