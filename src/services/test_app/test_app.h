#ifndef TEST_APP_H
#define TEST_APP_H

#include "services/gui/application.h"
#include "frames/test_app_main_frame.h"

struct TestApp
{
    OgfApplication *app;

    TestAppMainFrame *main_frame;
    //TestAppSecondFrame *second_frame;
};

void test_app_service(void *pvParams);

#endif
