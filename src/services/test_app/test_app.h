#ifndef TEST_APP_H
#define TEST_APP_H

//#include "services/gui/gui.h"
#include "services/gui/theater.h"
#include "services/gui/play.h"

#include "views/test_app_main_view.h"
#include "views/test_app_second_view.h"

struct TestApp
{
    //Gui *gui;
    Theater *theater;
    Play *play;

    TestAppMain *main_view;
    TestAppSecond *second_view;
};

enum TestAppViewId
{
    TestAppViewIdMain,
    TestAppViewIdSecond
};

void test_app_service(void *pvParams);

#endif
