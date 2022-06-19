#include "gui.h"

#include "services/input/input.h"
#include "mini_log.h"
#include "common.h"

#include "services.h"

Gui *gui_g;
extern Input *input_g;

Theater *gui_get_theater(Gui *gui)
{
    assert_ptr(gui);
    assert_ptr(gui->theater);
    return gui->theater;
}

static void gui_handle_input(Gui *gui, InputKey key)
{
    assert_ptr(gui);

    MLOG_D("Button press received: %d", key);

    if (gui->theater->play_count == 0)
    {
        MLOG_W("No active Plays found");
        return;
    }

    Play *current_play = theater_get_current_play(gui->theater);

    BaseType_t xStatus = xQueueSendToBack(current_play->event_queue, &key, portMAX_DELAY);
    if (xStatus != pdPASS)
    {
        MLOG_W("Could not send %d to the queue", key);
    }
}

static Gui *gui_alloc()
{
    Gui *gui = (Gui *) pvPortMalloc(sizeof(Gui));
    //gui->mutex = xSemaphoreCreateMutex();
    //xSemaphoreTake(gui->mutex, portMAX_DELAY);

    gui->display = (Display *) pvPortMalloc(sizeof(Display));
    display_init(gui->display, GUI_DISPLAY_WIDTH, GUI_DISPLAY_HEIGHT);
    display_draw_str_aligned(gui->display, CPC("OGF"), AlignmentCenter, AlignmentCenter);
    display_commit(gui->display);

    gui->theater = theater_alloc(gui->display);
    //xSemaphoreGive(gui->mutex);
    return gui;
}

void gui_service(void *pvParams)
{
    gui_g = gui_alloc();

    InputKey input_key;
    while (1)
    {
        if (xQueueReceive(input_g->event_queue,
                    &input_key,
                    portMAX_DELAY) == pdPASS)
        {
            gui_handle_input(gui_g, input_key);
        }
    }
    MLOG_E("Should never get here");
}
