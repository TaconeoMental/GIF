#ifndef GUI_APP_MANAGER_H
#define GUI_APP_MANAGER_H

#include "application.h"
#include "display.h"
#include "services/input/input.h"

#define MAX_APPLICATION_COUNT 5

struct ApplicationManager
{
    GifApplication **apps;
    uint8_t app_count;

    GifApplication *current_app;
};

ApplicationManager *application_manager_alloc();
void application_manager_add_application(ApplicationManager *app_manager, GifApplication *app);

#endif
