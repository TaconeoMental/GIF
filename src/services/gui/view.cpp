#include "view.h"

#include "common.h"

GifApplicationView *gif_application_view_alloc()
{
    GifApplicationView *view = (GifApplicationView *) pvPortMalloc(sizeof(GifApplicationView));
    return view;
}

void gif_application_view_set_frame(GifApplicationView *view, Frame *frame)
{
    assert_ptr(view);
    assert_ptr(frame);
    view->frame = frame;
}

void gif_application_view_set_event_handler(GifApplicationView *view, ViewInputHandler handler)
{
    assert_ptr(view);
    view->event_handler = handler;
}

void gif_application_view_set_handlers(GifApplicationView *view, ViewHandlers handlers)
{
    assert_ptr(view);
    view->handlers = handlers;
}

void gif_application_view_set_context(GifApplicationView *view, void *context)
{
    assert_ptr(view);
    assert_ptr(context);
    view->context = context;
}

void *gif_application_view_get_model(GifApplicationView *view)
{
    assert_ptr(view);
    return view->context;
}
