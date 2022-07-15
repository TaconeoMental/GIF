#include "test_app_main_frame.h"

TestAppMainFrame *test_app_main_frame_alloc()
{
    TestAppMainFrame *app_frame = (TestAppMainFrame *) pvPortMalloc(sizeof(TestAppMainFrame));
    app_frame->frame = frame_alloc(2, 1);
    frame_set_as_main(app_frame->frame);

    label_init(&app_frame->l1, "Arriba");
    label_grid(&app_frame->l1, app_frame->frame, 0, 0); //, NOCOLSPAN, NOSTICKY);

    Frame *bottom_frame = frame_alloc(1, 2);
    frame_grid(bottom_frame, app_frame->frame, 1, 0); //, NOCOLSPAN, NOSTICKY);

    label_init(&app_frame->l2, "Izq");
    label_grid(&app_frame->l2, bottom_frame, 0, 0); //, NOCOLSPAN, NOSTICKY);

    label_init(&app_frame->l4, "Der");
    label_grid(&app_frame->l4, bottom_frame, 0, 1); //, NOCOLSPAN, NOSTICKY);
                                                    //
    return app_frame;
}
