#ifndef TEST_APP_SECOND_VIEW
#define TEST_APP_MAIN_VIEW

#include "services/gui/view.h"
//#include "services/gui/display.h"

struct TestAppSecond
{
    View *view;
    void *context;
};

TestAppSecond *test_app_second_alloc();
void test_app_second_draw_callback(Display *display);
void test_app_second_input_callback();

#endif
