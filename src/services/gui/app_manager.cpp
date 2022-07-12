#include "app_manager.h"

ApplicationManager *application_manager_alloc()
{
    ApplicationManager *app_manager = (ApplicationManager *) pvPortMalloc(sizeof(ApplicationManager));
    app_manager->apps = (OgfApplication **) pvPortMalloc(MAX_APPLICATION_COUNT * sizeof(OgfApplication *));
    app_manager->app_count = 0;
    return app_manager;
}

void application_manager_add_application(ApplicationManager *app_manager,
                                         OgfApplication *app);
{
    assert_ptr(app_manager);
    assert_ptr(app);

    if (app_manager->app_count == MAX_APPLICATION_COUNT)
    {
        MLOG_E("Arreglo de aplicaciones lleno!");
        return;
    }
    app_manager->apps[app_manager->app_count++] = app;
    app_manager->current_app = app;
}
