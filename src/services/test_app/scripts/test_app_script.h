#ifndef TEST_APP_SCRIPT_H
#define TEST_APP_SCRIPT_H

#include "services/gui/play.h"

enum TestAppScene
{
    TestAppMain,
    TestAppSecond,
    TestAppCount
};

void test_app_main_on_enter(void *context);
void test_app_second_on_enter(void *context);

void test_app_main_on_input(void *context);
void test_app_second_on_input(void *context);

void test_app_main_on_exit(void *context);
void test_app_second_on_exit(void *context);

void test_app_second_draw_callback(Display *display);
void test_app_main_draw_callback(Display *display);

extern const ScriptHandlers test_app_script_handlers;

#endif
