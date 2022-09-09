#include "view.h"

#include "common.h"

OgfApplicationView *ogf_application_view_alloc()
{
    OgfApplicationView *view = (OgfApplicationView *) pvPortMalloc(sizeof(OgfApplicationView));
    return view;
}

void ogf_application_view_set_frame(OgfApplicationView *view, Frame *frame)
{
    assert_ptr(view);
    assert_ptr(frame);
    view->frame = frame;
}

void ogf_application_view_set_event_handler(OgfApplicationView *view, ViewInputHandler handler)
{
    assert_ptr(view);
    view->event_handler = handler;
}

void ogf_application_view_set_handlers(OgfApplicationView *view, ViewHandlers handlers)
{
    assert_ptr(view);
    view->handlers = handlers;
}

void ogf_application_view_set_context(OgfApplicationView *view, void *context)
{
    assert_ptr(view);
    assert_ptr(context);
    view->context = context;
}

void *ogf_application_view_get_model(OgfApplicationView *view)
{
    assert_ptr(view);
    return view->context;
}
