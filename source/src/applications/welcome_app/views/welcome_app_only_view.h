#ifndef WELCOME_APP_TEMPLATE_VIEW
#define WELCOME_APP_TEMPLATE_VIEW

#include "services/gui/widgets/label.h"
#include "services/gui/view.h"
#include "welcome_app_view.h"

typedef void (*WelcomeAppOnlyViewCallback)(WelcomeAppEvent event, void *context);

struct WelcomeAppOnlyViewModel
{
    Label label;
    Label label_2;
    Label label_3;

    void *callback_context;
    WelcomeAppOnlyViewCallback callback;
};

struct WelcomeAppOnlyView
{
    GifApplicationView *view;
    WelcomeAppOnlyViewModel *model;
};

WelcomeAppOnlyView *welcome_app_only_view_alloc();
void welcome_app_only_view_callback(WelcomeAppEvent event, void *context);
void welcome_app_only_view_handler(void *context, InputKey key);
void welcome_app_only_view_set_callback(WelcomeAppOnlyView *view, WelcomeAppOnlyViewCallback callback, void *context);
extern const ViewHandlers welcome_app_only_view_handlers;

#endif
