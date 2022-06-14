#include "view.h"

#include "common.h"


void view_set_draw_callback(View *view, ViewCallback callback)
{
    assert_ptr(view);
    view->draw_callback = callback;
}

void view_set_input_callback(View *view, ViewCallback callback)
{
    assert_ptr(view);
    view->input_callback = callback;
}

/*
void view_set_enter_callback(View *view, ViewCallback callback)
{
    assert_ptr(view);
    view->on_enter_callback = callback;
}

void view_set_exit_callback(View *view, ViewCallback callback)
{
    assert_ptr(view);
    view->on_exit_callback = callback;
}
*/
