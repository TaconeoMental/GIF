#ifndef TEST_APP_SECOND_VIEW_H
#define TEST_APP_SECOND_VIEW_H

#include "services/gui/widgets/frame.h"
#include "services/gui/widgets/label.h"
#include "services/gui/view.h"
#include "test_app_view.h"

typedef void (*TestAppSecondViewCallback)(TestAppEvent event, void* context);

struct TestAppSecondViewModel
{
    Label l1;
    Label l2;
    Label labels[3];
    uint8_t current_label;
    void *context; // TODO: Renombrar a "callback_context"
    TestAppSecondViewCallback callback;
};

struct TestAppSecondView
{
    OgfApplicationView *view;
    TestAppSecondViewModel *model;
};

TestAppSecondView *test_app_second_view_alloc();
void test_app_second_view_callback(TestAppEvent event, void *context);
void test_app_second_view_handler(void *context, InputKey key);
void test_app_second_view_set_callback(TestAppSecondView *view, TestAppSecondViewCallback callback, void *context);
extern const ViewHandlers test_app_second_view_handlers;

#endif
