#ifndef HID_APP_H
#define HID_APP_H

#include "services/gui/application.h"
#include "views/hid_app_template_view.h"

struct HidApp
{
    GifApplication *app;
    HidAppTemplateView *template_view;
};

void hid_app_service(void *pvParams);

#endif
