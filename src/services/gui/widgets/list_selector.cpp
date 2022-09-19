#include "list_selector.h"

#include "common.h"

void list_selector_model_fill_screen(ListSelectorModel *model)
{
    assert_ptr(model);

    char text[MAX_LABEL_TEXT_LENGTH];

    if (model->current_index > 0)
    {
        model->renderer(model->items[model->current_index - 1], text);
        label_set_text(&model->label_up, text);
    }
    else
    {
        label_set_text(&model->label_up, "");
    }

    model->renderer(model->items[model->current_index], text);
    label_set_text(&model->label_middle, text);

    if (model->current_index < model->total_items)
    {
        model->renderer(model->items[model->current_index + 1], text);
        label_set_text(&model->label_down, text);
    }
    else
    {
        label_set_text(&model->label_down, "");
    }
}

void list_selector_draw_callback(Display *display, Widget *widget)
{
    assert_ptr(display);
    assert_ptr(widget);
    ListSelectorModel *model = (ListSelectorModel *) widget->context;

    display_draw_frame(display, widget->x,
            widget->y,
            widget->width,
            widget->height);
    // TODO: WIDGET_DRAW(model->main_frame->widget, display)??
    model->main_frame->widget->draw_callback(display, model->main_frame->widget);
}

void list_selector_init(ListSelector *selector, uint8_t type)
{
    assert_ptr(selector);
    selector->widget = widget_alloc();
    widget_set_draw_callback(selector->widget, list_selector_draw_callback);

    ListSelectorModel *model = SIMPLE_ALLOC(ListSelectorModel);
    selector->model = model;

    model->main_frame = frame_alloc();
    model->current_index = 0;

    model->middle_frame = frame_alloc();

    // Init para dibujarlo
    frame_init_grid(model->main_frame, 1, 3);
    label_init(&model->label_up);
    label_init(&model->label_middle);
    label_init(&model->label_down);
    label_init_text(&model->l_arrow, ">");
    label_init_text(&model->r_arrow, "<");
    widget_set_context(selector->widget, model);
}

bool list_selector_input(ListSelector *selector, InputKey key, uint8_t *output)
{
    assert_ptr(selector);
    assert_ptr(output);
    ListSelectorModel *model = selector->model;
    uint8_t or_index = model->current_index;
    switch (key)
    {
        case InputKeyOk:
            *output = model->items[model->current_index];
            return true;
        case InputKeyRight: /* Bajar */
            if (or_index < model->total_items)
            {
                ++model->current_index;
            }
            break;
        case InputKeyLeft: /* Subir */
            if (or_index > 0)
            {
                --model->current_index;
            }
            break;
    }
    list_selector_model_fill_screen(model);
    return false;
}

// Setters
void list_selector_set_items(ListSelector *selector, ListSelectorItemType *arr, uint8_t arr_length, ListSelectorItemRenderer renderer)
{
    selector->model->total_items = arr_length - 1;
    selector->model->items = (uint8_t *) pvPortMalloc(arr_length * sizeof(uint8_t));
    memcpy(selector->model->items, arr, arr_length * sizeof(uint8_t)) ;
    selector->model->renderer = renderer;
    list_selector_model_fill_screen(selector->model);
}

// Posicionamiento
void list_selector_grid(ListSelector *selector, Frame *frame, uint8_t column, uint8_t row, uint8_t x_p, uint8_t y_p)
{
    assert_ptr(selector);
    assert_ptr(frame);

    ListSelectorModel *model = selector->model;
    frame_grid_widget(frame, selector->widget, column, row, x_p, y_p);

    widget_inherit_shape(model->main_frame->widget, selector->widget);
    label_grid(&model->label_up, model->main_frame, 0, 0, GIF_NO_PADDING);
    label_grid(&model->label_down, model->main_frame, 0, 2, GIF_NO_PADDING);

    frame_grid(model->middle_frame, model->main_frame, 0, 1, GIF_NO_PADDING);
    label_stack(&model->r_arrow, model->middle_frame, FRAME_STACK_RIGHT, 10, FRAME_STACK_FILL_Y);
    label_stack(&model->l_arrow, model->middle_frame, FRAME_STACK_LEFT, 10, FRAME_STACK_FILL_Y);
    label_stack(&model->label_middle, model->middle_frame, FRAME_STACK_RIGHT, FRAME_STACK_FILL_X, FRAME_STACK_FILL_Y);
}

void list_selector_stack(ListSelector *selector, Frame *frame, FrameStackDirection stack_dir, int8_t width, int8_t height)
{
    assert_ptr(selector);
    assert_ptr(frame);
    frame_stack_widget(frame, selector->widget, stack_dir, width, height);
}
