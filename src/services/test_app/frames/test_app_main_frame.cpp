#include "test_app_main_frame.h"

#include "common.h"

TestAppMainFrame *test_app_main_frame_alloc()
{
    TestAppMainFrame *app_frame = (TestAppMainFrame *) pvPortMalloc(sizeof(TestAppMainFrame));
    app_frame->frame = frame_alloc();
    frame_init_grid(app_frame->frame, 1, 2);

    frame_set_as_main(app_frame->frame);

    label_init(&app_frame->l1, "Arriba");
    label_grid(&app_frame->l1, app_frame->frame, 0, 0, OGF_NO_PADDING);

    Frame *bottom_frame = frame_alloc();
    frame_init_grid(bottom_frame, 5, 1);
    frame_set_border(bottom_frame, true);
    frame_grid(bottom_frame, app_frame->frame, 0, 1, OGF_NO_PADDING);

    label_init(&app_frame->l2, "1");
    label_set_border(&app_frame->l2, true);
    label_grid(&app_frame->l2, bottom_frame, 0, 0, OGF_PADDING(4));

    label_init(&app_frame->l2, "2");
    label_grid(&app_frame->l2, bottom_frame, 1, 0, OGF_PADDING(1));

    label_init(&app_frame->l3, "3");
    label_set_border(&app_frame->l3, true);
    label_grid(&app_frame->l3, bottom_frame, 2, 0, OGF_PADDING(4));

    label_init(&app_frame->l3, "4");
    label_grid(&app_frame->l3, bottom_frame, 3, 0, OGF_PADDING(1));

    label_init(&app_frame->l4, "5");
    label_set_border(&app_frame->l4, true);
    label_grid(&app_frame->l4, bottom_frame, 4, 0, OGF_PADDING(4));

    return app_frame;
}
