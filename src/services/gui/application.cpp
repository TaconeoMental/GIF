#include "application.h"

#include "display.h"
#include "resource.h"
#include "common.h"
#include "services/gui/gui.h"

GifApplication *gif_application_alloc()
{
    GifApplication *app = SIMPLE_ALLOC(GifApplication);
    app->gui = (Gui *) gif_resource_open("gui");
    app->event_queue = xQueueCreate(5, sizeof(GifApplicationEvent));
    app->indexed_views = gif_indexed_views_alloc();
    return app;
}

void gif_application_set_context(GifApplication *app, void *context)
{
    assert_ptr(app);
    assert_ptr(context);
    app->context = context;
}

void gif_application_attach_to_gui(GifApplication *app)
{
    assert_ptr(app);
    application_manager_add_application(app->gui->app_manager, app);
}

void gif_application_request_draw(GifApplication *app)
{
    assert_ptr(app);
    xEventGroupSetBits(app->gui->flags_event_group, GUI_FLAG_DRAW);
}

void gif_application_send_custom_event(GifApplication *app, uint8_t event)
{
    assert_ptr(app);
    GifApplicationEvent app_event;
    app_event.type = GifApplicationEventTypeCustom;
    app_event.data.custom_event = event;

    BaseType_t xStatus = xQueueSendToBack(app->event_queue, &app_event, portMAX_DELAY);
    if (xStatus != pdPASS)
    {
        MLOG_W("Could not send %d to the queue", app_event);
    }
}

void gif_application_add_view(GifApplication *app, uint8_t view_id, GifApplicationView *view)
{
    assert_ptr(app);
    assert_ptr(view);
    gif_indexed_views_add_view(app->indexed_views, view_id, view);
}

void gif_application_on_enter(GifApplication *app)
{
    assert_ptr(app);
    GifApplicationView *curr_view = gif_indexed_views_get_current(app->indexed_views);
    curr_view->handlers.on_enter_handler(app->context);
    gif_application_request_draw(app);
}

void gif_application_next_view(GifApplication *app, uint8_t view_id)
{
    assert_ptr(app);
    gif_indexed_views_set_current_id(app->indexed_views, view_id);
    gif_application_on_enter(app);
}

void gif_application_start(GifApplication *app)
{
    assert_ptr(app);

    InputKey input_key;
    GifApplicationEvent event;
    while (1)
    {
        if (xQueueReceive(app->event_queue,
                    &event,
                    portMAX_DELAY) == pdPASS)
        {
            GifApplicationView *curr_view = gif_indexed_views_get_current(app->indexed_views);
            MLOG_D("Event received TYPE=%d", event.type);
            if (event.type == GifApplicationEventTypeInput)
            {
                curr_view->event_handler(curr_view->context, event.data.key);
            } else
            {
                curr_view->handlers.on_event_handler(app->context, event);
            }
        }
    }
}
