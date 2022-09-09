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
    uint8_t current_label = 0;
    TestAppSecondViewCallback callback;
    void *context;
};

struct TestAppSecondView
{
    OgfApplicationView *view;
    TestAppSecondViewModel *model;
};

TestAppSecondView *test_app_second_view_alloc();
TestAppSecondViewModel *test_app_second_view_get_model(TestAppSecondView *view);
OgfApplicationView *test_app_second_view_get_view(TestAppSecondView *view);

extern const ViewHandlers test_app_second_view_handlers;

#endif
