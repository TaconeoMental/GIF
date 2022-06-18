#include "test_app_script.h"
#include "mini_log.h"
#include "services/gui/gui.h"

#include "../test_app.h"

void test_app_main_on_enter(void *context)
{
    MLOG_I("TestAppMain OnEnter");

    TestApp *app = context;
    theater_switch_to_view(app->theater, TestAppMain);
}

void test_app_main_on_input(void *context)
{

}

void test_app_second_on_exit(void *context)
{
    MLOG_I("TestAppMain OnExit");
}

void test_app_main_draw_callback(Display *display)
{
    display_draw_str(display, "TEST APP MAIN", 0, 0);
    display_commit(display);
}
