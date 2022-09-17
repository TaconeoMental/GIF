#include "test_app_main_view.h"

#include "common.h"
#include "services/gui/view.h"
#include "services/test_app/test_app.h"

TestAppMainView *test_app_main_view_alloc()
{
    TestAppMainView *main_view = SIMPLE_ALLOC(TestAppMainView);
    TestAppMainViewModel *model = SIMPLE_ALLOC(TestAppMainViewModel);
    main_view->model = model;

    main_view->view = ogf_application_view_alloc();
    Frame *main_frame = frame_alloc();

    frame_init_grid(main_frame, 2, 2);

    label_init(&model->title, "EJEMPLO!");
    label_init(&model->title2, ":D!");
    label_grid(&model->title, main_frame, 0, 1, OGF_NO_PADDING);
    label_grid(&model->title2, main_frame, 1, 0, OGF_NO_PADDING);

    ogf_application_view_set_event_handler(main_view->view, test_app_main_view_handler);
    ogf_application_view_set_handlers(main_view->view, test_app_main_view_handlers);
    ogf_application_view_set_frame(main_view->view, main_frame);
    ogf_application_view_set_context(main_view->view, model);

    return main_view;
}

void test_app_main_view_callback(TestAppEvent event, void *context)
{
    assert_ptr(context);
    TestApp *app = (TestApp *) context;

    if (event != TestAppMainEventOpenSecond)
    {
        MLOG_E("Unknown event Id=%d", event);
        return;
    }
    ogf_application_send_custom_event(app->app, event);
}

void test_app_main_view_handler(void *context, InputKey key)
{
    assert_ptr(context);
    TestAppMainViewModel *model = (TestAppMainViewModel *) context;
    if (key == InputKeyOk)
    {
        model->callback(TestAppMainEventOpenSecond, model->callback_context);
    }
}

void test_app_main_view_set_callback(TestAppMainView *view, TestAppMainViewCallback callback, void *context)
{
    assert_ptr(context);
    assert_ptr(callback);
    TestAppMainViewModel *model = view->model;
    model->callback = callback;
    model->callback_context = context;
}

// Context es la app normal
void test_app_main_view_on_enter(void *context)
{
    assert_ptr(context);
    TestApp *app = (TestApp *) context;
    test_app_main_view_set_callback(app->main_view, test_app_main_view_callback, app);
}

void test_app_main_view_on_event(void *context, OgfApplicationEvent event)
{
    assert_ptr(context);
    TestApp *app = (TestApp *) context;
    TestAppMainView *main_view = app->main_view;
    if (event.type == OgfApplicationEventTypeInput)
    {
        return;
    }

    switch (event.data.custom_event)
    {
        case TestAppMainEventOpenSecond:
            ogf_application_next_view(app->app, TestAppViewSecond);
            break;
        default:
            MLOG_D("Non actionable event received");
    }
}

void test_app_main_view_on_exit(void *context)
{
    assert_ptr(context);
    MLOG_D("Exiting");
}

const ViewHandlers test_app_main_view_handlers = {
    test_app_main_view_on_enter,
    test_app_main_view_on_event,
    test_app_main_view_on_exit
};
