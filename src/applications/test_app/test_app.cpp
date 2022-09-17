#include "test_app.h"

#include <freertos/FreeRTOS.h>

#include "common.h"
#include "resource.h"
#include "services/gui/gui.h"
#include "services/gui/application.h"
#include "views/test_app_view.h"
#include "views/test_app_second_view.h"
#include "views/test_app_main_view.h"

TestApp *test_app_alloc()
{
    TestApp *test_app = SIMPLE_ALLOC(TestApp);
    test_app->app = gif_application_alloc();
    gif_application_set_context(test_app->app, test_app);
    test_app->second_view = test_app_second_view_alloc();
    test_app->main_view = test_app_main_view_alloc();
    gif_application_add_view(
        test_app->app,
        TestAppViewMain,
        test_app->main_view->view);
    gif_application_add_view(
        test_app->app,
        TestAppViewSecond,
        test_app->second_view->view);
    gif_application_next_view(test_app->app, TestAppViewMain);
    gif_application_attach_to_gui(test_app->app);
    return test_app;
}

void test_app_free(TestApp *test_app)
{
    //app_free(test_app->app);
    free(test_app);
}

void test_app_service(void *pvParams)
{
    TestApp *test_app = test_app_alloc();

    gif_application_start(test_app->app);

    test_app_free(test_app);
}
