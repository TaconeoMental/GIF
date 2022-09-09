#ifndef TEST_APP_H
#define TEST_APP_H

#include "services/gui/application.h"
#include "views/test_app_second_view.h"

struct TestApp
{
    OgfApplication *app;
    TestAppSecondView *second_view;
};

void test_app_service(void *pvParams);

#endif
