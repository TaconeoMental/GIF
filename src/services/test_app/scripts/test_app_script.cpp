#include "test_app_script.h"

void (*const test_app_script_on_enter_handlers[])(void *context) = {
    test_app_main_on_enter,
    test_app_second_on_enter
};

void (*const test_app_script_on_input_handlers[])(void *context) = {
    test_app_main_on_input,
    test_app_second_on_input
};

void (*const test_app_script_on_exit_handlers[])(void *context) = {
    test_app_main_on_input,
    test_app_second_on_exit
};

void (*const test_app_script_draw_callbacks[])(Display *display) = {
    test_app_main_draw_callback,
    test_app_second_draw_callback
};

const ScriptHandlers test_app_script_handlers = {
    test_app_script_on_enter_handlers,
    test_app_script_on_input_handlers,
    test_app_script_on_exit_handlers,
    test_app_script_draw_callbacks,
    TestAppCount
};
