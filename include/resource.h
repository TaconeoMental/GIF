#ifndef OGF_RESOURCE_H
#define OGF_RESOURCE_H

#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>

#define MAX_RESOURCE_COUNT 5
#define MAX_RESOURCE_NAME_LENGTH 10

struct OgfResource
{
    void *data;
    char *name;
};

struct OgfResources
{
    OgfResource *resource_array;
    uint8_t resource_count;
};

extern OgfResources *resources_g;

OgfResources *ogf_resources_alloc();
void ogf_resource_create(const char *name, void *data);
void *ogf_resource_open(const char *name);

#endif
