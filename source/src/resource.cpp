#include "resource.h"

#include <string.h>
#include "common.h"

GifResources *resources_g;

GifResources *gif_resources_alloc()
{
    GifResources *resources = SIMPLE_ALLOC(GifResources);
    resources->resource_array = (GifResource *) pvPortMalloc(MAX_RESOURCE_COUNT * sizeof(GifResource));
    resources->resource_count = 0;
    return resources;
}

void gif_resource_create(const char *name, void *data)
{
    assert_ptr(resources_g);
    assert_c(strlen(name) < MAX_RESOURCE_NAME_LENGTH);

    if (resources_g->resource_count == MAX_RESOURCE_COUNT)
    {
        MLOG_E("Can not add shared resource '%s'!", name);
        return;
    }
    GifResource *res = &resources_g->resource_array[resources_g->resource_count++];

    // Alocamos y copiamos el nombre
    res->name = (char *) pvPortMalloc(MAX_RESOURCE_NAME_LENGTH + 1);
    strncpy(res->name, name, MAX_RESOURCE_NAME_LENGTH + 1);

    // Y ahora la data
    res->data = data;

    MLOG_T("%s: %x", res->name, res->data);
    MLOG_I("'%s' resource created succesfully", name);
}

// Creo que es el medio trucherío dividir un task en 2, pero funciona súper así
// que ñeee
void *gif_resource_open(const char *name)
{
    GifResource *resource;
    while (1)
    {
        for (uint8_t i = 0; i < resources_g->resource_count; i++)
        {
            GifResource *resource = &resources_g->resource_array[i];
            if (strcmp(name, resource->name) == 0)
            {
                // El recurso buscado existe!
                return resource->data;
            }
        }
        vTaskDelay(1);
    }
}
