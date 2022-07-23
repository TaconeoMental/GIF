#include "test_app_second_frame.h"

TestAppSecondFrame *test_app_second_frame_alloc()
{
    TestAppSecondFrame *app_frame = (TestAppSecondFrame *) pvPortMalloc(sizeof(TestAppSecondFrame));
    app_frame->frame = frame_alloc();

    /*
    label_init(&app_frame->l1, "Arriba");
    label_has_border(&app_frame->l1, true);
    //label_set_padding(&app_frame->l1, 1, 1);
    //label_pack(&app_frame->l1, app_frame->frame, FRAME_PACK_UP);

    Frame *bottom_frame = frame_alloc();
    frame_init_grid(bottom_frame, 3, 1);
    frame_grid(bottom_frame, app_frame->frame, 0, 1);

    label_init(&app_frame->l2, "Izq");
    label_has_border(&app_frame->l2, true);
    label_set_padding(&app_frame->l2, 1, 1);
    label_grid(&app_frame->l2, bottom_frame, 0, 0);

    label_init(&app_frame->l3, "Cen");
    label_has_border(&app_frame->l3, true);
    label_set_padding(&app_frame->l3, 1, 1);
    label_grid(&app_frame->l3, bottom_frame, 1, 0);

    label_init(&app_frame->l4, "Der");
    label_has_border(&app_frame->l4, true);
    label_set_padding(&app_frame->l4, 1, 1);
    label_grid(&app_frame->l4, bottom_frame, 2, 0);
    */

    return app_frame;
}
