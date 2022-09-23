#ifndef WELCOME_APP_H
#define WELCOME_APP_H

#include "services/gui/application.h"
#include "views/welcome_app_only_view.h"

struct WelcomeApp
{
    GifApplication *app;
    WelcomeAppOnlyView *only_view;
};

void welcome_app_service(void *pvParams);

#endif
