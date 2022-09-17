#ifndef GUI_VIEW_H
#define GUI_VIEW_H

#include "services/input/input.h"
#include "widgets/frame.h"
#include "application.h"

struct GifApplicationEvent;

typedef void (*ViewInputHandler)(void *context, InputKey key);
typedef void (*ViewEventHandler)(void *context, GifApplicationEvent event);
typedef void (*ViewGenericHandler)(void *context);

struct ViewHandlers
{
    ViewGenericHandler on_enter_handler;
    ViewEventHandler on_event_handler;
    ViewGenericHandler on_exit_handler;
};

struct GifApplicationView
{
    Frame *frame;
    ViewInputHandler event_handler;
    ViewHandlers handlers;
    void *context;
};

GifApplicationView *gif_application_view_alloc();
void gif_application_view_set_frame(GifApplicationView *view, Frame *frame);
void gif_application_view_set_event_handler(GifApplicationView *view, ViewInputHandler handler);
void gif_application_view_set_handlers(GifApplicationView *view, ViewHandlers handlers);
void gif_application_view_set_context(GifApplicationView *view, void *context);
void *gif_application_view_get_model(GifApplicationView *view);

#endif
