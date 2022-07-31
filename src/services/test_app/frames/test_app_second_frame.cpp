#include "test_app_second_frame.h"

TestAppSecondFrame *test_app_second_frame_alloc()
{
    TestAppSecondFrame *app_frame = (TestAppSecondFrame *) pvPortMalloc(sizeof(TestAppSecondFrame));
    app_frame->frame = frame_alloc();

    label_init(&app_frame->l1, "Arriba");
    label_stack(&app_frame->l1, app_frame->frame, FRAME_STACK_UP, FRAME_STACK_FILL_X, 15);

    Frame *bottom_frame = frame_alloc();
    frame_init_grid(bottom_frame, 3, 1);
    frame_stack(bottom_frame, app_frame->frame, FRAME_STACK_UP, FRAME_STACK_FILL_X, FRAME_STACK_FILL_Y);

    label_init(&app_frame->l2, "1");
    label_set_border(&app_frame->l2, true);
    label_grid(&app_frame->l2, bottom_frame, 0, 0, OGF_PADDING(0));

    label_init(&app_frame->l3, "2");
    label_grid(&app_frame->l3, bottom_frame, 1, 0, OGF_PADDING(0));

    label_init(&app_frame->l4, "3");
    label_set_border(&app_frame->l4, true);
    label_grid(&app_frame->l4, bottom_frame, 2, 0, OGF_PADDING(0));

    /*
    label_init(&app_frame->l3, "4");
    label_grid(&app_frame->l3, bottom_frame, 3, 0, OGF_PADDING(1));

    label_init(&app_frame->l4, "5");
    label_set_border(&app_frame->l4, true);
    label_grid(&app_frame->l4, bottom_frame, 4, 0, OGF_PADDING(4));
    */

    return app_frame;
}
