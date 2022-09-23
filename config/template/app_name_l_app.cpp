#include "root_defines.h"
#include "special.h"

#ifdef TO_BE_IGNORED
#include "views.h"
#endif

TYPE_ROOT_APP *UTIL_CONCAT(APP_NAME_L,_app_alloc())
{
    TYPE_ROOT_APP *UTIL_CONCAT(APP_NAME_L,_app) = SIMPLE_ALLOC(TYPE_ROOT_APP);
    VARIABLE_ROOT_APP->app = gif_application_alloc();
    CONFIG_ROOT_VIEWS_ALLOC
    CONFIG_ROOT_ADD_VIEWS
    gif_application_next_view(VARIABLE_ROOT_APP->app, UTIL_CONCAT(TYPE_ROOT_APP,View,VIEWS_FIRST));
    gif_application_attach_to_gui(VARIABLE_ROOT_APP->app);
    return VARIABLE_ROOT_APP;
}
