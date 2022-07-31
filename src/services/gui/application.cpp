#include "application.h"

#include "mini_log.h"
#include "resource.h"
#include "common.h"
#include "display.h"
#include "services/input/input.h"
#include "services/gui/gui.h"

OgfApplication *ogf_application_alloc()
{
    OgfApplication *app = (OgfApplication *) pvPortMalloc(sizeof(OgfApplication));
    app->event_queue = xQueueCreate(5, sizeof(InputKey));
    app->gui = (Gui *) ogf_resource_open("gui");
    return app;
}

void ogf_application_set_context(OgfApplication *app, void *context)
{
    assert_ptr(app);
    assert_ptr(context);
    app->context = context;
}

void ogf_application_set_frame(OgfApplication *app, Frame *frame)
{
    assert_ptr(app);
    assert_ptr(frame);
    app->current_frame = frame;
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

void ogf_application_start(OgfApplication *app)
{
    assert_ptr(app);

    ogf_application_request_draw(app);
    InputKey input_key;
    while (1)
    {
        if (xQueueReceive(app->event_queue,
                          &input_key,
                          portMAX_DELAY) == pdPASS)
        {
            MLOG_D("TODO");
        }
    }
}
