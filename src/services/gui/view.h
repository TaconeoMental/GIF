#ifndef GUI_VIEW_H
#define GUI_VIEW_H

#include "display.h"

typedef void (*ViewCallback)(void);
typedef void (*ViewDrawCallback)(Display *display);
//typedef (*ViewInputCallback)(void);

struct View
{
    ViewDrawCallback draw_callback;
    ViewCallback input_callback;

    //ViewCallback on_enter_callback;
    //ViewCallback on_exit_callback;
};

void view_set_draw_callback(View *view, ViewDrawCallback callback);
void view_set_input_callback(View *view, ViewCallback callback);

//void view_set_enter_callback(View *view, ViewCallback callback);
//void view_set_exit_callback(View *view, ViewCallback callback);

#endif
