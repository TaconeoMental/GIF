#include "test_app_script.h"

void (*const test_app_script_on_enter_handlers[])(void *context) = {
};

void (*const test_app_script_on_input_handlers[])(void *context) = {
};

void (*const test_app_script_on_exit_handlers[])(void *context) = {
};

const ScriptHandlers test_app_script_handlers = {
    test_app_script_on_enter_handlers,
    test_app_script_on_input_handlers,
    test_app_script_on_exit_handlers,
    TestAppCount
};
