#include "application.h"

#include "resource.h"
#include "common.h"
#include "display.h"
#include "services/input/input.h"
#include "services/gui/gui.h"

OgfApplication *ogf_application_alloc()
{
    OgfApplication *app = (OgfApplication *) pvPortMalloc(sizeof(OgfApplication));
    app->gui = (Gui *) ogf_resource_open("gui");
    app->event_queue = xQueueCreate(5, sizeof(OgfApplicationEvent));
    app->indexed_views = ogf_indexed_views_alloc();
    return app;
}

void ogf_application_set_context(OgfApplication *app, void *context)
{
    assert_ptr(app);
    assert_ptr(context);
    app->context = context;
}

void ogf_application_attach_to_gui(OgfApplication *app)
{
    assert_ptr(app);
    application_manager_add_application(app->gui->app_manager, app);
}

void ogf_application_request_draw(OgfApplication *app)
{
    assert_ptr(app);
    xEventGroupSetBits(app->gui->flags_event_group, GUI_FLAG_DRAW);
}

void ogf_application_send_custom_event(OgfApplication *app, uint8_t event)
{
    assert_ptr(app);
    OgfApplicationEvent app_event;
    app_event.type = OgfApplicationEventTypeCustom;
    app_event.data.custom_event = event;

    BaseType_t xStatus = xQueueSendToBack(app->event_queue, &app_event, portMAX_DELAY);
    if (xStatus != pdPASS)
    {
        MLOG_W("Could not send %d to the queue", app_event);
    }
}

void ogf_application_add_view(OgfApplication *app, uint8_t view_id, OgfApplicationView *view)
{
    assert_ptr(app);
    assert_ptr(view);
    ogf_indexed_views_add_view(app->indexed_views, view_id, view);
}

static OgfApplicationView *ogf_application_get_current_view(OgfApplication *app)
{
    assert_ptr(app);
    OgfApplicationView *curr_view = ogf_indexed_views_get_current(app->indexed_views);
    assert_ptr(curr_view);
    return curr_view;
}

static void ogf_application_on_enter(OgfApplication *app)
{
    MLOG_T("APP ON_ENTER");
    assert_ptr(app);

    OgfApplicationView *curr_view = ogf_application_get_current_view(app);
    curr_view->handlers.on_enter_handler(app);
}

void ogf_application_next_view(OgfApplication *app, uint8_t view_id)
{
    assert_ptr(app);
    ogf_indexed_views_set_current_id(app->indexed_views, view_id);
    ogf_application_on_enter(app);
}

void ogf_application_start(OgfApplication *app)
{
    assert_ptr(app);

    ogf_application_request_draw(app);
    InputKey input_key;
    OgfApplicationEvent event;
    while (1)
    {
        if (xQueueReceive(app->event_queue,
                    &event,
                    portMAX_DELAY) == pdPASS)
        {
            OgfApplicationView *curr_view = ogf_indexed_views_get_current(app->indexed_views);
            assert_ptr(curr_view);
            MLOG_D("Event received TYPE=%d", event.type);
            if (event.type == OgfApplicationEventTypeInput)
            {
                MLOG_T("WAS INPUT EVENT");
                curr_view->event_handler(curr_view->context, event.data.key);
            } else
            {
                curr_view->handlers.on_event_handler(app, event);
            }
            ogf_application_request_draw(app);
        }
    }
}
