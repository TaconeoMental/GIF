#include "indexed_view.h"

#include "common.h"

IndexedViews *gif_indexed_views_alloc()
{
    IndexedViews *indexed_views = SIMPLE_ALLOC(IndexedViews);
    indexed_views->current_view_id = 0;
    indexed_views->view_count = 0;
    return indexed_views;
}

void gif_indexed_views_add_view(IndexedViews *views, uint8_t id, GifApplicationView *view)
{
    assert_ptr(views);
    assert_c(id >= 0);
    assert_c(id < MAX_VIEW_COUNT);

   IndexedViewEntry *entry = &views->entries[views->view_count++];
   entry->view = view;
   entry->id = id;
}

GifApplicationView *gif_indexed_views_get_view(IndexedViews *views, uint8_t id)
{
    assert_ptr(views);
    assert_c(id >= 0);
    assert_c(id < MAX_VIEW_COUNT);

    for (uint8_t i = 0; i < MAX_VIEW_COUNT; i++)
    {
        IndexedViewEntry entry = views->entries[i];
        if (entry.id == id)
        {
            return entry.view;
        }
    }
}

void gif_indexed_views_set_current_id(IndexedViews *views, uint8_t id)
{
    assert_ptr(views);
    assert_c(id >= 0);
    assert_c(id < MAX_VIEW_COUNT);
    views->current_view_id = id;
}

GifApplicationView *gif_indexed_views_get_current(IndexedViews *views)
{
    assert_ptr(views);
    return gif_indexed_views_get_view(views, views->current_view_id);
}
