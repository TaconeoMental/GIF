#ifndef TEST_APP_SCRIPT_H
#define TEST_APP_SCRIPT_H

enum TestAppScene
{
    TestAppMain,
    TestAppSecond,
    TestAppCount
};

void test_app_main_on_enter(void *context);
void test_app_second_on_enter(void *context);

void test_app_main_on_input(void *context);
void test_app_main_on_input(void *context);

void test_app_second_on_exit(void *context);
void test_app_second_on_exit(void *context);

extern const ScriptHandlers test_app_script_handlers;

#endif
