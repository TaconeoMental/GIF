#ifndef TEST_APP_H
#define TEST_APP_H

struct TestApp
{
    OgfApplication *app;

    TestAppMainFrame *main_frame;
    TestAppSecondFrame *second_frame;
};

void test_app_service(void *pvParams);

#endif
