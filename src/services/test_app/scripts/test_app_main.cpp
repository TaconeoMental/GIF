#include "mini_log.h""

void test_app_main_on_enter(void *context)
{
    MLOG_I("TestAppMain OnEnter");
}

void test_app_main_on_input(void *context)
{

}

void test_app_second_on_exit(void *context)
{
    MLOG_I("TestAppMain OnExit");
}
