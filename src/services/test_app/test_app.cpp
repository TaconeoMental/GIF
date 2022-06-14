#include "test_app.h"


void test_app_init(TestApp *test_app)
{
    test_app->gui = gui_g;
    test_app->main_view = test_app_main_alloc();
    test_app->second_view = test_app_second_alloc();

    test_app->play = play_alloc();
    play_set_context(test_app->play, test_app);
    play_set_script_handlers(test_app->play, &test_app_script_handlers);
}


void test_app_free(TestApp *test_app)
{
    free(test_app->main_view);
}

void test_app_service(void *pvParams)
{
    TestApp *test_app;
    test_app_init(test_app);

    //theater_play(test_app->theater);

    test_app_free(test_app);
}
