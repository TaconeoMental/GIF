#include "application.h"

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

void ogf_application_draw(OgfApplication *app)
{
    frame_render(app->frame, app->gui->display);
}

void ogf_application_start(OgfApplication *app)
{
    assert_ptr(app);

    InputKey input_key;
    while (1)
    {
        if (xQueueReceive(app->event_queue,
                    &input_key,
                    portMAX_DELAY) == pdPASS)
        {
            //play_send_input(play, input_key);
        }
    }
}
