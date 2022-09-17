#include "gui.h"

#include "services/input/input.h"
#include "services/gui/view.h"
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

    // TODO: Hacer esto una función
    GifApplication *current_app = gui->app_manager->current_app;
    GifApplicationEvent event;
    event.type = GifApplicationEventTypeInput;
    event.data.key = key;

    BaseType_t xStatus = xQueueSendToBack(current_app->event_queue, &event, portMAX_DELAY);
    if (xStatus != pdPASS)
    {
        MLOG_W("Could not send %d to the queue", key);
    }
}

static void gui_redraw(Gui *gui)
{
    assert_ptr(gui);
    display_clear(gui->display);
    GifApplication *current_app = gui->app_manager->current_app;

    // GifApplicationView *view = current_app->views[current_app->current_view_id]->view;
    GifApplicationView *view = gif_indexed_views_get_current(current_app->indexed_views);
    // GifApplication *view = gif_application_get_current_view(current_app);

    Widget *widget = view->frame->widget;
    assert_ptr(widget);

    // Dibujamos el frame
    widget->draw_callback(gui->display, widget);
    display_commit(gui->display);
}

static Gui *gui_alloc()
{
    Gui *gui = (Gui *) pvPortMalloc(sizeof(Gui));
    gui->display = (Display *) pvPortMalloc(sizeof(Display));
    display_init(gui->display, GUI_DISPLAY_WIDTH, GUI_DISPLAY_HEIGHT);

    gui->flags_event_group = xEventGroupCreate();
    if (gui->flags_event_group == NULL)
    {
        MLOG_E("Could not create event group.");
    }

    gui->app_manager = application_manager_alloc();
    return gui;
}

void gui_service(void *pvParams)
{
    Gui *gui = gui_alloc();
    gif_resource_create("gui", gui);

    Input *input = (Input *) gif_resource_open("input");

    EventBits_t xEventGroupValue;
    while (1)
    {
        xEventGroupValue = xEventGroupWaitBits(gui->flags_event_group,
                                               GUI_FLAG_ALL,
                                               pdTRUE,
                                               pdFALSE,
                                               portMAX_DELAY
                                               );
        if (xEventGroupValue & GUI_FLAG_INPUT)
        {
            InputKey input_key;
            if (xQueueReceive(input->event_queue,
                                 &input_key,
                                 portMAX_DELAY) == pdPASS)
            {
                gui_handle_input(gui, input_key);
            }
        }

        if (xEventGroupValue & GUI_FLAG_DRAW)
        {
            gui_redraw(gui);
        }
    }
    MLOG_E("Should never get here");
}
