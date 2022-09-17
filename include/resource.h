#ifndef GIF_RESOURCE_H
#define GIF_RESOURCE_H

#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>

#define MAX_RESOURCE_COUNT 5
#define MAX_RESOURCE_NAME_LENGTH 10

struct GifResource
{
    void *data;
    char *name;
};

struct GifResources
{
    GifResource *resource_array;
    uint8_t resource_count;
};

extern GifResources *resources_g;

GifResources *gif_resources_alloc();
void gif_resource_create(const char *name, void *data);
void *gif_resource_open(const char *name);

#endif
