#ifndef GUI_H
#define GUI_H

#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>

#include "display.h"
#include "app_manager.h"
#include "application.h"

// Pantalla
#define GUI_DISPLAY_WIDTH 128
#define GUI_DISPLAY_HEIGHT 64

struct Gui
{
    Display *display;
    ApplicationManager *app_manager;
};

void gui_add_application(Gui *gui, OgfApplication *app);
void gui_request_redraw(Gui *gui);

#endif
