#pragma once
#include "special.h"
#include "util_defines.h"
#include "root_defines.h"

#define CALLBACK_T UTIL_CONCAT(TYPE_ROOT_APP,VIEW_NAME_T,ViewCallback)
#define MODEL_T UTIL_CONCAT(TYPE_ROOT_APP,VIEW_NAME_T,ViewModel)
#define MAIN_VIEW_T UTIL_CONCAT(TYPE_ROOT_APP,VIEW_NAME_T,View)
#define FUNC_START_L UTIL_CONCAT(VARIABLE_ROOT_APP,_,VIEW_NAME_L,_view_)

typedef void (*CALLBACK_T)(UTIL_CONCAT(TYPE_ROOT_APP,Event) event, void* context);

struct CUSTOM_MODEL_NAME;

struct MODEL_T
{
    MODEL_S custom_model;
    void *callback_context;
    CALLBACK_T callback;
};

struct MAIN_VIEW_T
{
    GifApplicationView *view;
    MODEL_T *model;
};

MAIN_VIEW_T *UTIL_CONCAT(FUNC_START_L,alloc());
void UTIL_CONCAT(FUNC_START_L,callback)(VIEWS_ENUM_TYPE event, void *context);
void UTIL_CONCAT(FUNC_START_L,handler)(void *context, InputKey key);
void UTIL_CONCAT(FUNC_START_L,set_callback)(MAIN_VIEW_T *view, CALLBACK_T callback, void *context);
extern const ViewHandlers UTIL_CONCAT(FUNC_START_L,handlers);
