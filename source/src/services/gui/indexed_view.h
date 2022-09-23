#ifndef GIF_INDEXED_VIEW_H
#define GIF_INDEXED_VIEW_H

#include "common.h"

struct GifApplicationView;

#define MAX_VIEW_COUNT 10

struct IndexedViewEntry
{
    GifApplicationView *view;
    uint8_t id;
};

struct IndexedViews
{
    IndexedViewEntry entries[MAX_VIEW_COUNT];
    uint8_t current_view_id;
    uint8_t view_count;
};

IndexedViews *gif_indexed_views_alloc();
void gif_indexed_views_add_view(IndexedViews *views, uint8_t id, GifApplicationView *view);
GifApplicationView *gif_indexed_views_get_view(IndexedViews *views, uint8_t id);
void gif_indexed_views_set_current_id(IndexedViews *views, uint8_t id);
GifApplicationView *gif_indexed_views_get_current(IndexedViews *views);

#endif
