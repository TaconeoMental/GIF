#include "test_app_second_view.h"

#include <stdlib.h>
#include "common.h"
#include "services/gui/view.h"
#include "services/test_app/test_app.h"

struct TestApp;

void test_app_second_view_handler(void *context, InputKey key);

TestAppSecondView *test_app_second_view_alloc()
{
    TestAppSecondView *app_view = SIMPLE_ALLOC(TestAppSecondView);
    TestAppSecondViewModel *model = SIMPLE_ALLOC(TestAppSecondViewModel);

    app_view->view = ogf_application_view_alloc();
    Frame *main_frame = frame_alloc();

    // TODO: meter todo esto en view_alloc
    //frame_set_as_main(app_frame->frame);

    label_init(&model->l1, "Arriba");
    label_set_border(&model->l1, true);
    label_stack(&model->l1, main_frame, FRAME_STACK_UP, FRAME_STACK_FILL_X, 15);

    Frame *bottom_frame = frame_alloc();
    frame_init_grid(bottom_frame, 3, 1);
    frame_stack(bottom_frame, main_frame, FRAME_STACK_DOWN, FRAME_STACK_FILL_X, 20);

    char num_s[2];
    for (uint8_t i = 0; i < 3; i++)
    {
        Label *curr_label = &model->labels[i];
        sprintf(num_s, "%d", i + 1);
        label_init(curr_label, num_s);
        label_set_round_border(curr_label, true);
        label_grid(curr_label, bottom_frame, i, 0, OGF_NO_PADDING);
    }
    label_set_fill(&model->labels[0], true);

    label_init(&model->l2, "DER");
    label_stack(&model->l2, main_frame, FRAME_STACK_RIGHT, 40, FRAME_STACK_FILL_Y);

    ogf_application_view_set_event_handler(app_view->view, test_app_second_view_handler);
    ogf_application_view_set_handlers(app_view->view, test_app_second_view_handlers);
    ogf_application_view_set_frame(app_view->view, main_frame);
    ogf_application_view_set_context(app_view->view, model);

    return app_view;
}

TestAppSecondViewModel *test_app_second_view_get_model(TestAppSecondView *view)
{
    assert_ptr(view);
    return view->model;
}

OgfApplicationView *test_app_second_view_get_view(TestAppSecondView *view)
{
    assert_ptr(view);
    return view->view;
}

void test_app_second_view_set_callback(TestAppSecondView *view, TestAppSecondViewCallback callback, void *context)
{
    assert_ptr(context);
    TestAppSecondViewModel *model = test_app_second_view_get_model(view);
    model->callback = callback;
    model->context = context;
}

void test_app_second_view_callback(TestAppEvent event, void *context)
{
    assert_ptr(context);
    TestApp *app = (TestApp *) context;

    if (event != TestAppSecondEventOpenMain)
    {
        MLOG_E("Unknown event Id=%d", event);
        return;
    }
    ogf_application_send_custom_event(app->app, event);
}

void test_app_second_view_handler(void *context, InputKey key)
{
    assert_ptr(context);
    TestAppSecondView *view = (TestAppSecondView *) context;
    TestAppSecondViewModel *model = test_app_second_view_get_model(view);

    uint8_t or_label = model->current_label;
    switch (key)
    {
        case InputKeyRight:
            model->current_label = (model->current_label + 1) % 3;
            label_set_fill(&model->labels[model->current_label], true);
            label_set_fill(&model->labels[or_label], false);
            break;
        case InputKeyLeft:
            model->current_label = (model->current_label - 1) % 3;
            label_set_fill(&model->labels[model->current_label], true);
            label_set_fill(&model->labels[or_label], false);
            break;
        case InputKeyOk:
            model->callback(TestAppSecondEventOpenMain, model->context);
    }
}

// Context es la app normal
void test_app_second_view_on_enter(void *context)
{
    assert_ptr(context);
    TestApp *app = (TestApp *) context;
    TestAppSecondView *second_view = app->second_view;
    test_app_second_view_set_callback(second_view, test_app_second_view_callback, app);
}

void test_app_second_view_on_event(void *context, OgfApplicationEvent event)
{
    assert_ptr(context);
    TestApp *app = (TestApp *) context;
    TestAppSecondView *second_view = app->second_view;
    if (event.type == OgfApplicationEventTypeInput)
    {
        return;
    }

    switch (event.data.custom_event)
    {
        case TestAppSecondEventOpenMain:
            //ogf_application_next_view(app, TestAppViewMain);
            MLOG_D("OPENMAINEVENT");
            break;
        default:
            MLOG_D("Non actionable event received");
    }
}

void test_app_second_view_on_exit(void *context)
{
    assert_ptr(context);
    MLOG_D("Exiting");
}

const ViewHandlers test_app_second_view_handlers = {
    test_app_second_view_on_enter,
    test_app_second_view_on_event,
    test_app_second_view_on_exit
};
