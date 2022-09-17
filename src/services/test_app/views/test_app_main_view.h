#ifndef TEST_APP_MAIN_VIEW
#define TEST_APP_MAIN_VIEW

#include "services/gui/widgets/frame.h"
#include "services/gui/widgets/label.h"
#include "services/gui/view.h"
#include "test_app_view.h"

typedef void (*TestAppMainViewCallback)(TestAppEvent event, void* context);

struct TestAppMainViewModel
{
    Label title;
    Label title2;

    // TODO: Ver si meto esto en su propia estructura
    void *callback_context;
    TestAppMainViewCallback callback;
};

struct TestAppMainView
{
    OgfApplicationView *view;
    TestAppMainViewModel *model;
};

TestAppMainView *test_app_main_view_alloc();
void test_app_main_view_callback(TestAppEvent event, void *context);
void test_app_main_view_handler(void *context, InputKey key);
void test_app_main_view_set_callback(TestAppMainView *view, TestAppMainViewCallback callback, void *context);
extern const ViewHandlers test_app_main_view_handlers;

#endif
