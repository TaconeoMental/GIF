#include "indexed_view.h"

#include "common.h"

IndexedViews *ogf_indexed_views_alloc()
{
    IndexedViews *indexed_views = SIMPLE_ALLOC(IndexedViews);
    indexed_views->current_view_id = 0;
    indexed_views->view_count = 0;
    return indexed_views;
}

void ogf_indexed_views_add_view(IndexedViews *views, uint8_t id, OgfApplicationView *view)
{
    assert_ptr(views);
    assert_c(id >= 0);
    assert_c(id < MAX_VIEW_COUNT);
    views->views[id] = view; // XD
    ++views->view_count;
}

OgfApplicationView *ogf_indexed_views_get_view(IndexedViews *views, uint8_t id)
{
    assert_ptr(views);
    assert_c(id >= 0);
    assert_c(id < MAX_VIEW_COUNT);
    OgfApplicationView *view = views->views[id];
    assert_ptr(view);
    return view;
}

void ogf_indexed_views_set_current_id(IndexedViews *views, uint8_t id)
{
    assert_ptr(views);
    assert_c(id >= 0);
    assert_c(id < MAX_VIEW_COUNT);
    views->current_view_id = id;
}

OgfApplicationView *ogf_indexed_views_get_current(IndexedViews *views)
{
    assert_ptr(views);
    return ogf_indexed_views_get_view(views, views->current_view_id);
}
