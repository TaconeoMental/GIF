#include "{app_name}.h"

#include <freertos/FreeRTOS.h>

#include "common.h"
#include "services/gui/application.h"
#include "views/{app_name}_view.h"
#include "views/{app_name}_template_view.h"

{App_Name} *{app_name}_alloc()
{
    {App_Name} *{app_name} = SIMPLE_ALLOC({App_Name});
    {app_name}->app = gif_application_alloc();
    gif_application_set_context({app_name}->app, {app_name});

    {app_name}->template_view = {app_name}_template_view_alloc();
    gif_application_add_view(
            {app_name}->app,
            {App_Name}ViewTemplate,
            {app_name}->template_view->view);

    gif_application_next_view({app_name}->app, {App_Name}ViewTemplate);
    gif_application_attach_to_gui({app_name}->app);
    return {app_name};
}

void {app_name}_free({App_Name} *{app_name})
{
    assert_ptr({app_name});
    free({app_name});
}

void {app_name}_service(void *pvParams)
{
    {App_Name} *{app_name} = {app_name}_alloc();

    gif_application_start({app_name}->app);

    {app_name}_free({app_name});
}
