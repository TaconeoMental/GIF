#include "test_app_second_view.h"

TestAppSecond *test_app_second_alloc()
{
    TestAppSecond *second = malloc(sizeof(TestAppSecond));
    view_set_context(second->view, second);
    view_set_draw_callback(second->view, test_app_second_draw_callback);
    //view_set_input_callback(main->view, test_app_main_input_callback);

    return second;
}

void test_app_second_draw_callback(Display *display)
{
    display_draw_str(display, "TEST APP SECOND", 0, 0);
    display_commit(display);
}

void test_app_second_input_callback()
{
    // idk
}
