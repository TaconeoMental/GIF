#include "resource.h"

#include <string.h>
#include "common.h"

OgfResources *resources_g;

OgfResources *ogf_resources_alloc()
{
    OgfResources *resources = (OgfResources *) pvPortMalloc(sizeof(OgfResources));
    resources->resource_array = (OgfResource *) pvPortMalloc(MAX_RESOURCE_COUNT * sizeof(OgfResource));
    resources->resource_count = 0;
    return resources;
}

void ogf_resource_create(char *name, void *data)
{
    assert_ptr(resources_g);
    assert_c(strlen(name) < MAX_RESOURCE_NAME_LENGTH);

    if (resources_g->resource_count == MAX_RESOURCE_COUNT)
    {
        MLOG_E("Can not add shared resource '%s'!", name);
        return;
    }
    OgfResource *res = &resources_g->resource_array[resources_g->resource_count++];

    // Alocamos y copiamos el nombre
    res->name = (char *) pvPortMalloc(MAX_RESOURCE_NAME_LENGTH + 1);
    strncpy(res->name, name, MAX_RESOURCE_NAME_LENGTH + 1);

    // Y ahora la data
    res->data = data;

    MLOG_T("%s: %x", res->name, res->data);
    MLOG_I("'%s' resource created succesfully", name);
    //MLOG_I("'%s' resource created succesfully", resources_g->resource_array[resources_g->resource_count - 1].name);
}

// Creo que es el medio trucherío dividir un task en 2, pero funciona súper así
// que ñeee
void *ogf_resource_open(char *name)
{
    OgfResource *resource;
    while (1)
    {
        for (uint8_t i = 0; i < resources_g->resource_count; i++)
        {
            OgfResource *resource = &resources_g->resource_array[i];
            if (strcmp(name, resource->name) == 0)
            {
                // El recurso buscado existe!
                return resource->data;
            }
        }
        vTaskDelay(1);
    }
}
