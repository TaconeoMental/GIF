#ifndef {APP_NAME}_TEMPLATE_VIEW
#define {APP_NAME}_TEMPLATE_VIEW

#include "services/gui/widgets/label.h"
#include "services/gui/view.h"
#include "{app_name}_view.h"

typedef void (*{App_Name}TemplateViewCallback)({App_Name}Event event, void* context);

struct {App_Name}TemplateViewModel
{
    Label title;

    void *callback_context;
    {App_Name}TemplateViewCallback callback;
};

struct {App_Name}TemplateView
{
    GifApplicationView *view;
    {App_Name}TemplateViewModel *model;
};

{App_Name}TemplateView *{app_name}_template_view_alloc();
void {app_name}_template_view_callback({App_Name}Event event, void *context);
void {app_name}_template_view_handler(void *context, InputKey key);
void {app_name}_template_view_set_callback({App_Name}TemplateView *view, {App_Name}TemplateViewCallback callback, void *context);
extern const ViewHandlers {app_name}_template_view_handlers;

#endif
