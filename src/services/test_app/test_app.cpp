#include "test_app.h"

#include "common.h"
#include "resource.h"

#include <freertos/FreeRTOS.h>

static TestApp *test_app_alloc()
{
    TestApp *test_app = (TestApp *) pvPortMalloc(sizeof(TestApp));
    test_app->app = ogf_application_alloc();
    ogf_application_set_context(test_app->app, test_app);

    test_app->main_frame = test_app_main_frame_alloc();
    ogf_application_set_frame(test_app->app, test_app->main_frame);

    gui_add_application(test_app->app->gui, app);

    return test_app;
}

void test_app_free(TestApp *test_app)
{
    app_free(test_app->app);
    free(test_app);
}

void test_app_service(void *pvParams)
{
    TestApp *test_app = test_app_alloc();

    ogf_application_start(test_app->app);

    test_app_free(test_app);
}
