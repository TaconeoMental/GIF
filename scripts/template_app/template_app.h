#ifndef {APP_NAME}_H
#define {APP_NAME}_H

#include "services/gui/application.h"
#include "views/{app_name}_template_view.h"

struct {App_Name}
{
    GifApplication *app;
    {App_Name}TemplateView *template_view;
};

void {app_name}_service(void *pvParams);

#endif
