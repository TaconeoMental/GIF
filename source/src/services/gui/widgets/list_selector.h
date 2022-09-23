#ifndef WIDGET_LIST_SELECTOR
#define WIDGET_LIST_SELECTOR

#include "widget.h"
#include "frame.h"
#include "services/gui/display.h"
#include "services/input/input.h"
#include "services/gui/widgets/label.h"
#include "services/gui/widgets/frame.h"

typedef void (*ListSelectorItemRenderer)(uint8_t num, char *out);

typedef uint8_t ListSelectorItemType;
#define ListSelectorItemSize sizeof(uint8_t)

#define LIST_SELECTOR_RENDERER_SIMPLE 1

struct ListSelectorModel
{
    uint8_t *items; // OWO
    uint8_t total_items;
    uint8_t current_index;
    ListSelectorItemRenderer renderer;

    // Menú
    Label label_up;
    Label label_middle;
    Label label_down;
    Label l_arrow;
    Label r_arrow;
    Frame *main_frame;
    Frame *middle_frame;
};

struct ListSelector
{
    Widget *widget;
    ListSelectorModel *model;
};

void list_selector_init(ListSelector *selector, uint8_t type);
bool list_selector_input(ListSelector *selector, InputKey key, uint8_t *output);

// Setters
void list_selector_set_items(ListSelector *seelctor, ListSelectorItemType *arr, uint8_t arr_length, ListSelectorItemRenderer renderer);

// Posicionamiento
void list_selector_grid(ListSelector *selector, Frame *frame, uint8_t column, uint8_t row, uint8_t x_p, uint8_t y_p);
void list_selector_stack(ListSelector *selector, Frame *frame, FrameStackDirection stack_dir, int8_t width, int8_t height);

#endif
