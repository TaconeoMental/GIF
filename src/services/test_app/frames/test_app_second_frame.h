#ifndef TEST_APP_SECOND_FRAME_H
#define TEST_APP_SECOND_FRAME_H

#include "services/gui/widgets/frame.h"
#include "services/gui/widgets/label.h"

struct TestAppSecondFrame
{
    Frame *frame;

    Label l1;
    Label l2;
    Label l3;
    Label l4;
};

TestAppSecondFrame *test_app_second_frame_alloc();

#endif
