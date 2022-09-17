#ifndef GUI_H
#define GUI_H

#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>
#include <freertos/event_groups.h>

#include "display.h"
#include "app_manager.h"
#include "application.h"

// Pantalla
#define GUI_DISPLAY_WIDTH 128
#define GUI_DISPLAY_HEIGHT 64

// Event flag bits
#define GUI_FLAG_INPUT (1 << 0)
#define GUI_FLAG_DRAW (1 << 1)
#define GUI_FLAG_ALL (GUI_FLAG_INPUT | GUI_FLAG_DRAW)

struct Gui
{
    Display *display;
    ApplicationManager *app_manager;
    EventGroupHandle_t flags_event_group;
};

void gui_add_application(Gui *gui, GifApplication *app);
void gui_request_redraw(Gui *gui);

#endif
