#ifndef TEST_APP_H
#define TEST_APP_H

//#include "services/gui/gui.h"
#include "services/gui/theater.h"
#include "services/gui/play.h"

struct TestApp
{
    //Gui *gui;
    //Theater *theater;
    Play *play;
};

void test_app_service(void *pvParams);

#endif
