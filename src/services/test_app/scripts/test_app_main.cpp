#include "test_app_script.h"
#include "mini_log.h"
#include "services/gui/gui.h"
#include "common.h"

#include "../test_app.h"

void test_app_main_on_enter(void *context)
{
    MLOG_I("TestAppMain OnEnter");

    //TestApp *app = context;
}

void test_app_main_on_input(void *context)
{

}

void test_app_main_on_exit(void *context)
{
    MLOG_I("TestAppMain OnExit");
}

void test_app_main_draw_callback(Display *display)
{
    display_draw_str(display, CPC("TEST APP MAIN"), 0, 0);
    display_commit(display);
}
