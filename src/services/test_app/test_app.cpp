#include "test_app.h"

void test_app_init(TestApp *test_app)
{
    test_app->theater = gui_get_theater(gui_g);
    test_app->main_view = test_app_main_alloc();
    test_app->second_view = test_app_second_alloc();

    test_app->play = play_alloc();
    play_set_context(test_app->play, test_app);
    play_set_script_handlers(test_app->play, &test_app_script_handlers);

    play_add_view(test_app->play,
            TestAppViewIdMain,
            test_app_main_get_view(test_app->main_view));

    play_add_view(test_app->play,
            TestAppViewIdSecond,
            test_app_second_get_view(test_app->second_view));

    play_next_scene(test_app->play, TestAppMain);
}


void test_app_free(TestApp *test_app)
{
    free(test_app->main_view);
    play_free(test_app->play);
}

void test_app_service(void *pvParams)
{
    TestApp *test_app;
    test_app_init(test_app);

    while (1)
    {
        // TODO
    }

    test_app_free(test_app);
}
