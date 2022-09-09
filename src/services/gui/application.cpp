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
    ogf_indexed_views_init(&app->views);
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
    ogf_indexed_views_add_view(&app->views, view_id, view);
}

static void ogf_application_on_enter(OgfApplication *app)
{
    assert_ptr(app);
    OgfApplicationView *curr_view = ogf_indexed_views_get_current(&app->views);
    assert_ptr(curr_view);
    curr_view->handlers.on_enter_handler(app);
}

void ogf_application_next_view(OgfApplication *app, uint16_t view_id)
{
    assert_ptr(app);
    ogf_indexed_views_set_current_id(&app->views, view_id);
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
            MLOG_D("TODO");
        }
    }
}
