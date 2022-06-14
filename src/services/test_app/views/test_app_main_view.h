#ifndef TEST_APP_MAIN_VIEW
#define TEST_APP_MAIN_VIEW

#include "services/gui/view.h"
//#include "services/gui/display.h"

struct TestAppMain
{
    View *view;
    void *context;
};

TestAppMain *test_app_main_alloc();
void test_app_main_draw_callback(Display *display);
void test_app_main_input_callback();

#endif
