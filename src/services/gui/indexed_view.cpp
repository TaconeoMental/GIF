#include "indexed_view.h"

#include "common.h"

void ogf_indexed_views_init(IndexedViews *views)
{
    assert_ptr(views);
    views->current_view_id = 0;
    views->view_count = 0;
}

void ogf_indexed_views_add_view(IndexedViews *views, uint8_t id, OgfApplicationView *view)
{
    assert_ptr(views);
    assert_c(id < MAX_VIEW_COUNT);
    IndexedViewsEntry new_entry = {id, view};
    views->entries[id] = new_entry;
    ++views->view_count;
}

void ogf_indexed_views_set_current_id(IndexedViews *views, uint8_t id)
{
    assert_ptr(views);
    views->current_view_id = id;
}

OgfApplicationView *ogf_indexed_views_get_current(IndexedViews *views)
{
    assert_ptr(views);
    for (int i = 0; i < views->view_count; i++)
    {
        OgfApplicationView *view = views->entries[i].view;
        if (view)
        {
            MLOG_W("NUM %d", i);
        }
    }
    return views->entries[views->current_view_id].view;
}
