#include "gui.h"

#include "services/input/input.h"
#include "mini_log.h"
#include "common.h"

// Que cada Play tenga su propio queue y que el gui envíe el input
// específicamente al queue en el top del stack (Play activo)
Gui gui_g;
extern Input input_g;

static void gui_handle_input(Gui *gui, InputKey key)
{
    MLOG_D("Button press received: %d", key);
    theater_send_input(gui->theater, key);
}

static void gui_init(Gui *gui)
{
    assert_ptr(gui);

    gui->display = (Display *) pvPortMalloc(sizeof(Display));
    display_init(gui->display, GUI_DISPLAY_WIDTH, GUI_DISPLAY_HEIGHT);
}

void gui_service_init()
{
    gui_init(&gui_g);
}

void gui_service(void *pvParams)
{
    InputKey input_key;
    while (1)
    {
        if (xQueueReceive(input_g.event_queue,
                          &input_key,
                          portMAX_DELAY) == pdPASS)
        {
            gui_handle_input(&gui_g, input_key);
        }
    }

    MLOG_E("Should never get here");
}
