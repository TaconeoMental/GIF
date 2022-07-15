#include "gui.h"

#include "services/input/input.h"
#include "mini_log.h"
#include "common.h"

#include "services.h"
#include "resource.h"

static void gui_handle_input(Gui *gui, InputKey key)
{
    assert_ptr(gui);

    MLOG_D("Button press received: %d", key);

    if (gui->app_manager->app_count == 0)
    {
        MLOG_W("No active apps found");
        return;
    }

    OgfApplication *current_app = gui->app_manager->current_app;

    BaseType_t xStatus = xQueueSendToBack(current_app->event_queue, &key, portMAX_DELAY);
    if (xStatus != pdPASS)
    {
        MLOG_W("Could not send %d to the queue", key);
    }

    display_commit(gui->display);
}

void gui_add_application(Gui *gui, OgfApplication *app)
{
    application_manager_add_application(gui->app_manager, app);
    gui_request_redraw(gui);
}

void gui_request_redraw(Gui *gui)
{
    ogf_application_draw(gui->app_manager->current_app);
}

static Gui *gui_alloc()
{
    Gui *gui = (Gui *) pvPortMalloc(sizeof(Gui));

    gui->display = (Display *) pvPortMalloc(sizeof(Display));
    display_init(gui->display, GUI_DISPLAY_WIDTH, GUI_DISPLAY_HEIGHT);

    gui->app_manager = application_manager_alloc();
    return gui;
}

void gui_service(void *pvParams)
{
    Gui *gui = gui_alloc();
    ogf_resource_create("gui", gui);

    Input *input = (Input *) ogf_resource_open("input");

    InputKey input_key;

    while (1)
    {
        if (xQueueReceive(input->event_queue,
                    &input_key,
                    portMAX_DELAY) == pdPASS)
        {
            gui_handle_input(gui, input_key);
        }
    }
    MLOG_E("Should never get here");
}
