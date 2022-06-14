#ifndef TEST_APP_H
#define TEST_APP_H

#include "services/gui/gui.h"

#include "views/test_app_main_view.h"
#include "views/test_app_second_view.h"

struct TestApp
{
    Gui *gui;

    TestAppMain *main_view;
    TestAppSecond *second_view;
};

void test_app_service(void *pvParams);

#endif
