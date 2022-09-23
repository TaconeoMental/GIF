#include <string.h>

void int_to_string_renderer(uint8_t n, char *out)
{
    const char *text;
    switch (n)
    {
        case 1:
            text = "uno";
            break;
        case 2:
            text = "dos";
            break;
        case 3:
            text = "tres";
            break;
        case 4:
            text = "cuatro";
            break;
        case 5:
            text = "cinco";
            break;
    }
    strncpy(out, text, MAX_LABEL_TEXT_LENGTH);
}

struct MODEL_S
{
    ListSelector list_selector;
    Label label;
    uint8_t number_list[5];
    uint8_t selected;
}

VIEW_INIT(INIT_ARGS)
{
    uint8_t number_list[] = {1, 2, 3, 4, 5};
    frame_init_grid(MAIN_FRAME, 2, 1);
    list_selector_init(MODEL(list_selector), LIST_SELECTOR_RENDERER_SIMPLE);
    list_selector_set_items(MODEL(list_selector),
            number_list,
            COUNT_OF(number_list),
            int_to_string_renderer);
    list_selector_grid(MODEL(list_selector), MAIN_FRAME, 0, 0, GIF_NO_PADDING);
    label_init_text(MODEL(label), "?");
    label_grid(MODEL(label), MAIN_FRAME, 1, 0, GIF_PADDING(10));
    label_set_border(MODEL(label), true);
    label_set_round_border(MODEL(label), true);
}

ON_EVENT(EVENT_ARGS)
{
    ON_EVENT(Redraw)
        APP_REDRAW;
}

INPUT_HANDLER(INPUT_ARGS)
{
    bool res = list_selector_input(MODEL(list_selector), KEY_OK, MODEL(selected));
    if (res)
    {
        char N[2];
        sprintf(N, "%d", MODEL(selected));
        label_set_text(MODEL(label), N);
    }
}
