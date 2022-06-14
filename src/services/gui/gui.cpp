#include "gui.h"

#include "services/input/input.h"
#include "mini_log.h"
#include "display.h"

Gui gui_g;
extern Input input_g;

static void gui_handle_input(Gui *gui, InputKey key)
{
    /*
    */
    display_clear(gui->display);
    switch (key)
    {
    case InputKeyLeft:
        display_draw_box_aligned(gui->display, 10, 30, AlignmentLeft, AlignmentCenter);
        break;
    case InputKeyOk:
        display_draw_box_aligned(gui->display, 10, 30, AlignmentCenter, AlignmentCenter);
        break;
    case InputKeyRight:
        display_draw_box_aligned(gui->display, 10, 30, AlignmentRight, AlignmentCenter);
        break;
    default:
        display_draw_box_aligned(gui->display, 5, 5, AlignmentCenter, AlignmentCenter);
    }
    display_commit(gui->display);
}

static void gui_init(Gui *gui)
{
    gui->display = (Display *) pvPortMalloc(sizeof(Display));
    display_init(gui->display, GUI_DISPLAY_WIDTH, GUI_DISPLAY_HEIGHT);
    //view_port_init(gui->view_port);
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
            MLOG_D("Button press received: %d", input_key);
            gui_handle_input(&gui_g, input_key);
        }
    }

    MLOG_E("Should never get here");
}
