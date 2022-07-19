#include "application.h"

#include "mini_log.h"
#include "resource.h"
#include "common.h"
#include "services/input/input.h"
#include "gui.h"
#include "display.h"

OgfApplication *ogf_application_alloc()
{
    OgfApplication *app = (OgfApplication *) pvPortMalloc(sizeof(OgfApplication));
    app->event_queue = xQueueCreate(5, sizeof(InputKey));

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

void ogf_application_draw(OgfApplication *app)
{
    //frame_render(app->frame, app->gui->display);
}

void ogf_application_start(OgfApplication *app)
{
    assert_ptr(app);

    Gui *gui = (Gui *) ogf_resource_open("gui");

    Widget *widget = app->current_frame->widget;
    assert_ptr(widget);

    widget->draw_callback(gui->display, widget);
    display_commit(gui->display);

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
