#include "test_app_main_view.h"

TestAppMain *test_app_main_alloc()
{
    TestAppMain *main = malloc(sizeof(TestAppMain));
    view_set_context(main->view, main);
    view_set_draw_callback(main->view, test_app_main_draw_callback);
    //view_set_input_callback(main->view, test_app_main_input_callback);

    return main;
}

void test_app_main_draw_callback(Display *display)
{
    display_draw_str(display, "TEST APP MAIN", 0, 0);
    display_commit(display);
}

void test_app_main_input_callback()
{
    // idk
}
