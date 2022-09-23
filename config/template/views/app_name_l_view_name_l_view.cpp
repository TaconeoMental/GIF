#include "util_defines.h"
#include "custom_file_defines.h"
#include "special.h"

#ifdef OWO
    #include UTIL_STR(VIEW_NAME_L.h)
#endif

#define VIEW_NAME_VARIABLE UTIL_CONCAT(VIEW_NAME_L,_view)
#define CALLBACK_T UTIL_CONCAT(TYPE_ROOT_APP,VIEW_NAME_T,ViewCallback)
#define MODEL_T UTIL_CONCAT(TYPE_ROOT_APP,VIEW_NAME_T,ViewModel)
#define MAIN_VIEW_T UTIL_CONCAT(TYPE_ROOT_APP,VIEW_NAME_T,View)
#define MAIN_VIEW_L UTIL_CONCAT(VARIABLE_ROOT_APP,VIEW_NAME_L,View)
#define FUNC_START_L UTIL_CONCAT(VARIABLE_ROOT_APP,_,VIEW_NAME_L,_view_)

#define FUNC_ON_EXIT UTIL_CONCAT(FUNC_START_L,on_exit)
#define FUNC_ON_ENTER UTIL_CONCAT(FUNC_START_L,on_enter)
#define FUNC_ON_EVENT UTIL_CONCAT(FUNC_START_L,on_event)


MAIN_VIEW_T *UTIL_CONCAT(FUNC_START_L,alloc())
{
    MAIN_VIEW_T *VIEW_NAME_VARIABLE = SIMPLE_ALLOC(MAIN_VIEW_T);
    MODEL_T *model = SIMPLE_ALLOC(MODEL_T);
    VIEW_NAME_VARIABLE->model = model;
    VIEW_NAME_VARIABLE->view = gif_application_view_alloc();
    Frame *frame = frame_alloc();

    custom_view_init(frame, model);

    gif_application_view_set_event_handler(VIEW_NAME_VARIABLE->view, UTIL_CONCAT(FUNC_START_L,handler));
    gif_application_view_set_handlers(VIEW_NAME_VARIABLE->view, UTIL_CONCAT(FUNC_START_L,handlers));
    gif_application_view_set_frame(VIEW_NAME_VARIABLE->view, frame);
    gif_application_view_set_context(VIEW_NAME_VARIABLE->view, model);
    return VIEW_NAME_VARIABLE;
}

void UTIL_CONCAT(FUNC_START_L,callback)(VIEWS_ENUM_TYPE event, void *context)
{
    assert_ptr(context);
    TYPE_ROOT_APP *app = (TYPE_ROOT_APP *) context;
    gif_application_send_custom_event(app->app, event);
}

void UTIL_CONCAT(FUNC_START_L,handler)(void *context, InputKey key)
{
    assert_ptr(context);
    MODEL_T *model = (MODEL_T *) context;
    custom_input_handler(model, key);
}

void UTIL_CONCAT(FUNC_START_L,set_callback)(MAIN_VIEW_T *view, CALLBACK_T callback, void *context)
{
    assert_ptr(context);
    assert_ptr(callback);
    TestAppMainViewModel *model = view->model;
    model->callback = callback;
    model->callback_context = context;
}

// Context es la app normal
void FUNC_ON_ENTER(void *context)
{
    assert_ptr(context);
    TestApp *app = (TestApp *) context;
    test_app_main_view_set_callback(app->main_view, test_app_main_view_callback, app);
}

void FUNC_ON_EVENT(void *context, GifApplicationEvent event)
{
    assert_ptr(context);
    TestApp *app = (TestApp *) context;
    TestAppMainView *main_view = app->main_view;
    if (event.type == GifApplicationEventTypeInput)
    {
    }
    else
    {
        switch (event.data.custom_event)
        {
            default:
                MLOG_D("Non actionable event received");
        }
    }
}

void FUNC_ON_EXIT(void *context)
{
    assert_ptr(context);
    MLOG_D("Exiting");
}

const ViewHandlers test_app_main_view_handlers = {
    FUNC_ON_ENTER,
    FUNC_ON_EVENT,
    FUNC_ON_EXIT
};
