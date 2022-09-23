#pragma once
#include "root_defines.h"
#include "special.h"

struct TYPE_ROOT_APP
{
    GifApplication *app;
    CONFIG_ROOT_VIEWS_DEFINITIONS
};

void UTIL_CONCAT(VARIABLE_ROOT_APP,_service)(void *pvParams);
