#include "hid_app_template_view.h"

#include "common.h"
#include "services/gui/view.h"
#include "applications/hid_app/hid_app.h"

HidAppTemplateView *hid_app_template_view_alloc()
{
    HidAppTemplateView *template_view = SIMPLE_ALLOC(HidAppTemplateView);
    HidAppTemplateViewModel *model = SIMPLE_ALLOC(HidAppTemplateViewModel);
    template_view->model = model;

    template_view->view = gif_application_view_alloc();
    Frame *frame = frame_alloc();

    frame_init_grid(frame, 1, 1);

    label_init(&model->title, "Welcome :)");
    label_grid(&model->title, frame, 0, 0, GIF_NO_PADDING);

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
    // model->callback(HidAppTemplateEventOpenSecond, model->callback_context);
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
    HidAppTemplateView *template_view = app->template_view;
    if (event.type == GifApplicationEventTypeInput)
    {
        // Consume input
        return;
    }

    switch (event.data.custom_event)
    {
        default:
            // consume event
            return;
    }
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
