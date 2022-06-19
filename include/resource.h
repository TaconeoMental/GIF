#ifndef OGF_RESOURCE_H
#define OGF_RESOURCE_H

#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>

struct OgfResource
{
    void *data;
    char *name;
    SemaphoreHandle_t resource_mutex;
};

#endif
