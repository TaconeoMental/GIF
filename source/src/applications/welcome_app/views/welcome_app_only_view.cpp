#include "welcome_app_only_view.h"

#include "common.h"
#include "services/gui/view.h"
#include "applications/welcome_app/welcome_app.h"


WelcomeAppOnlyView *welcome_app_only_view_alloc()
{
    WelcomeAppOnlyView *only_view = SIMPLE_ALLOC(WelcomeAppOnlyView);
    WelcomeAppOnlyViewModel *model = SIMPLE_ALLOC(WelcomeAppOnlyViewModel);
    only_view->model = model;
    only_view->view = gif_application_view_alloc();
    Frame *frame = frame_alloc();
    frame_init_grid(frame, 1, 5);

    label_init_text(&model->label, "GIF");
    label_grid(&model->label, frame, 0, 1, GIF_NO_PADDING);

    label_init_text(&model->label, "Free and Open Source");
    label_grid(&model->label, frame, 0, 2, GIF_NO_PADDING);

    label_init_text(&model->label, "GUI Framework");
    label_grid(&model->label, frame, 0, 3, GIF_NO_PADDING);

    gif_application_view_set_event_handler(only_view->view, welcome_app_only_view_handler);
    gif_application_view_set_handlers(only_view->view, welcome_app_only_view_handlers);
    gif_application_view_set_frame(only_view->view, frame);
    gif_application_view_set_context(only_view->view, model);

    return only_view;
}

void welcome_app_only_view_callback(WelcomeAppEvent event, void *context)
{
    assert_ptr(context);
    WelcomeApp *app = (WelcomeApp *) context;
    gif_application_send_custom_event(app->app, event);
}

void welcome_app_only_view_handler(void *context, InputKey key)
{
    assert_ptr(context);
    WelcomeAppOnlyViewModel *model = (WelcomeAppOnlyViewModel *) context;
}

void welcome_app_only_view_set_callback(WelcomeAppOnlyView *view, WelcomeAppOnlyViewCallback callback, void *context)
{
    assert_ptr(context);
    assert_ptr(callback);
    WelcomeAppOnlyViewModel *model = view->model;
    model->callback = callback;
    model->callback_context = context;
}

void welcome_app_only_view_on_enter(void *context)
{
    assert_ptr(context);
    WelcomeApp *app = (WelcomeApp *) context;
    welcome_app_only_view_set_callback(app->only_view, welcome_app_only_view_callback, app);
}

void welcome_app_only_view_on_event(void *context, GifApplicationEvent event)
{
    assert_ptr(context);
    WelcomeApp *app = (WelcomeApp *) context;
    if (event.type == GifApplicationEventTypeInput) return;

    gif_application_request_draw(app->app);
}

void welcome_app_only_view_on_exit(void *context)
{
    assert_ptr(context);
    MLOG_D("Exiting");
}

const ViewHandlers welcome_app_only_view_handlers = {
    welcome_app_only_view_on_enter,
    welcome_app_only_view_on_event,
    welcome_app_only_view_on_exit
};
