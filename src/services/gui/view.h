#ifndef GUI_VIEW_H
#define GUI_VIEW_H

#include "services/input/input.h"
#include "widgets/frame.h"
#include "application.h"

struct OgfApplicationEvent;

typedef void (*ViewInputHandler)(void *context, InputKey key);
typedef void (*ViewEventHandler)(void *context, OgfApplicationEvent event);
typedef void (*ViewGenericHandler)(void *context);

struct ViewHandlers
{
    ViewGenericHandler on_enter_handler;
    ViewEventHandler on_event_handler;
    ViewGenericHandler on_exit_handler;
};

struct OgfApplicationView
{
    Frame *frame;
    ViewInputHandler event_handler;
    ViewHandlers handlers;
    void *context;
};

OgfApplicationView *ogf_application_view_alloc();
void ogf_application_view_set_frame(OgfApplicationView *view, Frame *frame);
void ogf_application_view_set_event_handler(OgfApplicationView *view, ViewInputHandler handler);
void ogf_application_view_set_handlers(OgfApplicationView *view, ViewHandlers handlers);
void ogf_application_view_set_context(OgfApplicationView *view, void *context);
void *ogf_application_view_get_model(OgfApplicationView *view);

#endif
