#include "test_app.h"

#include "scripts/test_app_script.h"
#include "services/gui/gui.h"
#include "common.h"

#include <freertos/FreeRTOS.h>

extern Gui *gui_g;

static TestApp *test_app_alloc()
{
    TestApp *test_app = (TestApp *) pvPortMalloc(sizeof(TestApp));
    test_app->play = play_alloc();
    play_set_context(test_app->play, test_app);
    play_set_script_handlers(test_app->play, &test_app_script_handlers);
    play_next_scene(test_app->play, TestAppMain);

    return test_app;
}

void test_app_free(TestApp *test_app)
{
    play_free(test_app->play);
    free(test_app);
}

void test_app_service(void *pvParams)
{
    TestApp *test_app = test_app_alloc();

    play_start(test_app->play);

    test_app_free(test_app);
}
