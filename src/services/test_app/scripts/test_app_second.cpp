#include "test_app_script.h"
#include "mini_log.h"
#include "services/gui/gui.h"
#include "common.h"

#include "../test_app.h"

void test_app_second_on_enter(void *context)
{
    MLOG_I("TestAppSecond OnEnter");

    TestApp *app = (TestApp*)context;
    play_switch_to_scene(app->play, TestAppSecond);
}

void test_app_second_on_input(void *context)
{

}

void test_app_second_on_exit(void *context)
{
    MLOG_I("TestAppSecond OnExit");
}

void test_app_second_draw_callback(Display *display)
{
    display_draw_str(display, CPC("TEST APP SECOND"), 0, 0);
    display_commit(display);
}
