#ifndef TEST_APP_MAIN_FRAME
#define TEST_APP_MAIN_FRAME

#include "services/gui/frame.h"
#include "services/gui/widgets/label.h"

struct TestAppMainFrame
{
    Frame *frame;
    char *title;

    Label l1;
    Label l2;
    Label l3;
    Label l4;
};

TestAppMainFrame *test_app_main_frame_alloc();

#endif
