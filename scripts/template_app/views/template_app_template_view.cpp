#include "{app_name}_template_view.h"

#include "common.h"
#include "services/gui/view.h"
#include "applications/{app_name}/{app_name}.h"

{App_Name}TemplateView *{app_name}_template_view_alloc()
{
    {App_Name}TemplateView *template_view = SIMPLE_ALLOC({App_Name}TemplateView);
    {App_Name}TemplateViewModel *model = SIMPLE_ALLOC({App_Name}TemplateViewModel);
    template_view->model = model;

    template_view->view = gif_application_view_alloc();
    Frame *frame = frame_alloc();

    frame_init_grid(frame, 1, 1);

    label_init(&model->title, "Welcome :)");
    label_grid(&model->title, frame, 0, 0, GIF_NO_PADDING);

    gif_application_view_set_event_handler(template_view->view, {app_name}_template_view_handler);
    gif_application_view_set_handlers(template_view->view, {app_name}_template_view_handlers);
    gif_application_view_set_frame(template_view->view, frame);
    gif_application_view_set_context(template_view->view, model);

    return template_view;
}

void {app_name}_template_view_callback({App_Name}Event event, void *context)
{
    assert_ptr(context);
    {App_Name} *app = ({App_Name} *) context;
    gif_application_send_custom_event(app->app, event);
}

void {app_name}_template_view_handler(void *context, InputKey key)
{
    assert_ptr(context);
    {App_Name}TemplateViewModel *model = ({App_Name}TemplateViewModel *) context;
    // model->callback({App_Name}TemplateEventOpenSecond, model->callback_context);
}

void {app_name}_template_view_set_callback({App_Name}TemplateView *view, {App_Name}TemplateViewCallback callback, void *context)
{
    assert_ptr(context);
    assert_ptr(callback);
    {App_Name}TemplateViewModel *model = view->model;
    model->callback = callback;
    model->callback_context = context;
}

void {app_name}_template_view_on_enter(void *context)
{
    assert_ptr(context);
    {App_Name} *app = ({App_Name} *) context;
    {app_name}_template_view_set_callback(app->template_view, {app_name}_template_view_callback, app);
}

void {app_name}_template_view_on_event(void *context, GifApplicationEvent event)
{
    assert_ptr(context);
    {App_Name} *app = ({App_Name} *) context;
    {App_Name}TemplateView *template_view = app->template_view;
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

void {app_name}_template_view_on_exit(void *context)
{
    assert_ptr(context);
    MLOG_D("Exiting");
}

const ViewHandlers {app_name}_template_view_handlers = {
    {app_name}_template_view_on_enter,
    {app_name}_template_view_on_event,
    {app_name}_template_view_on_exit
};
