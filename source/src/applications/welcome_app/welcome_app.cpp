#include "welcome_app.h"

#include <freertos/FreeRTOS.h>

#include "common.h"
#include "services/gui/application.h"
#include "views/welcome_app_view.h"
#include "views/welcome_app_only_view.h"

WelcomeApp *welcome_app_alloc()
{
    WelcomeApp *welcome_app = SIMPLE_ALLOC(WelcomeApp);
    welcome_app->app = gif_application_alloc();
    gif_application_set_context(welcome_app->app, welcome_app);

    welcome_app->only_view = welcome_app_only_view_alloc();
    gif_application_add_view(
            welcome_app->app,
            WelcomeAppViewOnly,
            welcome_app->only_view->view);

    gif_application_next_view(welcome_app->app, WelcomeAppViewOnly);
    gif_application_attach_to_gui(welcome_app->app);
    return welcome_app;
}

void welcome_app_free(WelcomeApp *welcome_app)
{
    assert_ptr(welcome_app);
    free(welcome_app);
}

void welcome_app_service(void *pvParams)
{
    WelcomeApp *welcome_app = welcome_app_alloc();
    gif_application_start(welcome_app->app);
    welcome_app_free(welcome_app);
}
