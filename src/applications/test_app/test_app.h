#ifndef TEST_APP_H
#define TEST_APP_H

#include "services/gui/application.h"
#include "views/test_app_second_view.h"
#include "views/test_app_main_view.h"

struct TestApp
{
    GifApplication *app;
    TestAppSecondView *second_view;
    TestAppMainView *main_view;
};

void test_app_service(void *pvParams);

#endif
