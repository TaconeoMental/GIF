#ifndef HID_APP_TEMPLATE_VIEW
#define HID_APP_TEMPLATE_VIEW

#include "services/gui/widgets/label.h"
#include "services/gui/view.h"
#include "hid_app_view.h"

typedef void (*HidAppTemplateViewCallback)(HidAppEvent event, void* context);

struct HidAppTemplateViewModel
{
    Label title;

    void *callback_context;
    HidAppTemplateViewCallback callback;
};

struct HidAppTemplateView
{
    GifApplicationView *view;
    HidAppTemplateViewModel *model;
};

HidAppTemplateView *hid_app_template_view_alloc();
void hid_app_template_view_callback(HidAppEvent event, void *context);
void hid_app_template_view_handler(void *context, InputKey key);
void hid_app_template_view_set_callback(HidAppTemplateView *view, HidAppTemplateViewCallback callback, void *context);
extern const ViewHandlers hid_app_template_view_handlers;

#endif
