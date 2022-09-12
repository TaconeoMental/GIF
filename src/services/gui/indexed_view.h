#ifndef OGF_INDEXED_VIEW_H
#define OGF_INDEXED_VIEW_H

#include "common.h"

struct OgfApplicationView;

#define MAX_VIEW_COUNT 10

struct IndexedViews
{
    OgfApplicationView *views[MAX_VIEW_COUNT];
    uint8_t current_view_id;
    uint8_t view_count;
};

IndexedViews *ogf_indexed_views_alloc();
void ogf_indexed_views_add_view(IndexedViews *views, uint8_t id, OgfApplicationView *view);
OgfApplicationView *ogf_indexed_views_get_view(IndexedViews *views, uint8_t id);
void ogf_indexed_views_set_current_id(IndexedViews *views, uint8_t id);
OgfApplicationView *ogf_indexed_views_get_current(IndexedViews *views);

#endif
