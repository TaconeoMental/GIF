#include "hid_app.h"

#include <freertos/FreeRTOS.h>

#include "common.h"
#include "services/gui/application.h"
#include "views/hid_app_view.h"
#include "views/hid_app_template_view.h"

HidApp *hid_app_alloc()
{
    HidApp *hid_app = SIMPLE_ALLOC(HidApp);
    hid_app->app = gif_application_alloc();
    gif_application_set_context(hid_app->app, hid_app);

    hid_app->template_view = hid_app_template_view_alloc();
    gif_application_add_view(
            hid_app->app,
            HidAppViewTemplate,
            hid_app->template_view->view);

    gif_application_next_view(hid_app->app, HidAppViewTemplate);
    gif_application_attach_to_gui(hid_app->app);
    return hid_app;
}

void hid_app_free(HidApp *hid_app)
{
    assert_ptr(hid_app);
    free(hid_app);
}

void hid_app_service(void *pvParams)
{
    HidApp *hid_app = hid_app_alloc();

    gif_application_start(hid_app->app);

    hid_app_free(hid_app);
}
