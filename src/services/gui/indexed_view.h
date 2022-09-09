#ifndef OGF_INDEXED_VIEW_H
#define OGF_INDEXED_VIEW_H

#include "common.h"

struct OgfApplicationView;

#define MAX_VIEW_COUNT 10

struct IndexedViewsEntry
{
    uint8_t id;
    OgfApplicationView *view;
};

struct IndexedViews
{
    IndexedViewsEntry entries[MAX_VIEW_COUNT];
    uint8_t current_view_id;
    uint8_t view_count;
};

void ogf_indexed_views_init(IndexedViews *views);
void ogf_indexed_views_add_view(IndexedViews *views, uint8_t id, OgfApplicationView *view);
void ogf_indexed_views_set_current_id(IndexedViews *views, uint8_t id);
OgfApplicationView *ogf_indexed_views_get_current(IndexedViews *views);

#endif
