#include "hid_app_template_view.h"

#include "common.h"
#include "services/gui/view.h"
#include "applications/hid_app/hid_app.h"

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

HidAppTemplateView *hid_app_template_view_alloc()
{
    HidAppTemplateView *template_view = SIMPLE_ALLOC(HidAppTemplateView);
    HidAppTemplateViewModel *model = SIMPLE_ALLOC(HidAppTemplateViewModel);
    template_view->model = model;
    template_view->view = gif_application_view_alloc();
    Frame *frame = frame_alloc();
    frame_init_grid(frame, 2, 1);

    uint8_t number_list[] = {1, 2, 3, 4, 5};

    list_selector_init(&model->list_selector, LIST_SELECTOR_RENDERER_SIMPLE);
    list_selector_set_items(&model->list_selector,
            number_list,
            COUNT_OF(number_list),
            int_to_string_renderer);
    list_selector_grid(&model->list_selector, frame, 0, 0, GIF_NO_PADDING);

    label_init_text(&model->label, "?");
    label_grid(&model->label, frame, 1, 0, GIF_PADDING(10));
    label_set_border(&model->label, true);
    label_set_round_border(&model->label, true);

    gif_application_view_set_event_handler(template_view->view, hid_app_template_view_handler);
    gif_application_view_set_handlers(template_view->view, hid_app_template_view_handlers);
    gif_application_view_set_frame(template_view->view, frame);
    gif_application_view_set_context(template_view->view, model);

    return template_view;
}

void hid_app_template_view_callback(HidAppEvent event, void *context)
{
    assert_ptr(context);
    HidApp *app = (HidApp *) context;
    gif_application_send_custom_event(app->app, event);
}

void hid_app_template_view_handler(void *context, InputKey key)
{
    assert_ptr(context);
    HidAppTemplateViewModel *model = (HidAppTemplateViewModel *) context;
    bool res = list_selector_input(&model->list_selector, key, &model->selected);
    if (res)
    {
        char N[2];
        sprintf(N, "%d", model->selected);
        label_set_text(&model->label, N);
    }
    model->callback(HidAppTemplateEventRedraw, model->callback_context);
}

void hid_app_template_view_set_callback(HidAppTemplateView *view, HidAppTemplateViewCallback callback, void *context)
{
    assert_ptr(context);
    assert_ptr(callback);
    HidAppTemplateViewModel *model = view->model;
    model->callback = callback;
    model->callback_context = context;
}

void hid_app_template_view_on_enter(void *context)
{
    assert_ptr(context);
    HidApp *app = (HidApp *) context;
    hid_app_template_view_set_callback(app->template_view, hid_app_template_view_callback, app);
}

void hid_app_template_view_on_event(void *context, GifApplicationEvent event)
{
    assert_ptr(context);
    HidApp *app = (HidApp *) context;
    if (event.type == GifApplicationEventTypeInput) return;

    gif_application_request_draw(app->app);
}

void hid_app_template_view_on_exit(void *context)
{
    assert_ptr(context);
    MLOG_D("Exiting");
}

const ViewHandlers hid_app_template_view_handlers = {
    hid_app_template_view_on_enter,
    hid_app_template_view_on_event,
    hid_app_template_view_on_exit
};
