#include "test_app_second_frame.h"

#include "common.h"

TestAppSecondFrame *test_app_second_frame_alloc()
{
    TestAppSecondFrame *app_frame = (TestAppSecondFrame *) pvPortMalloc(sizeof(TestAppSecondFrame));
    app_frame->frame = frame_alloc();
    frame_set_as_main(app_frame->frame);

    label_init(&app_frame->l1, "Arriba");
    label_set_border(&app_frame->l1, true);
    label_stack(&app_frame->l1, app_frame->frame, FRAME_STACK_UP, FRAME_STACK_FILL_X, 15);

    Frame *bottom_frame = frame_alloc();
    frame_init_grid(bottom_frame, 3, 1);
    frame_stack(bottom_frame, app_frame->frame, FRAME_STACK_DOWN, FRAME_STACK_FILL_X, 20);

    label_init(&app_frame->l2, "1");
    label_set_fill(&app_frame->l2, true);
    label_set_round_border(&app_frame->l2, true);
    label_grid(&app_frame->l2, bottom_frame, 0, 0, OGF_NO_PADDING);

    label_init(&app_frame->l3, "2");
    label_grid(&app_frame->l3, bottom_frame, 1, 0, OGF_PADDING(0));

    label_init(&app_frame->l4, "3");
    label_set_border(&app_frame->l4, true);
    label_set_round_border(&app_frame->l4, true);
    label_grid(&app_frame->l4, bottom_frame, 2, 0, OGF_PADDING(0));

    label_init(&app_frame->l5, "DER");
    label_stack(&app_frame->l5, app_frame->frame, FRAME_STACK_RIGHT, 40, FRAME_STACK_FILL_Y);

    return app_frame;
}
