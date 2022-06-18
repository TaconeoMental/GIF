#ifndef GUI_PLAY_H
#define GUI_PLAY_H

#include "display.h"
#include "services/input/input.h"

#define MAX_VIEWS 10

typedef void (*ScriptHandler)(void *context);
typedef void (*ScriptDrawCallback)(Display *display);

struct ScriptHandlers
{
    const ScriptHandler *on_enter_handlers;
    const ScriptHandler *on_input_handlers;
    const ScriptHandler *on_exit_handlers;
    const ScriptDrawCallback *draw_callbacks;
    uint8_t scene_count;
};

struct Play
{
    ScriptHandlers *script;

    uint8_t current_scene_id;
    uint8_t next_scene_id;

    void *context;
};

Play *play_alloc();
void play_free(Play *play);

void play_set_context(Play *play, void *context);
void play_set_script_handlers(Play *play, ScriptHandlers *handlers);

void play_next_scene(Play *play, uint8_t scene_id);
void play_enter_scene(Play *play);
void play_switch_to_scene(Play *play, uint8_t scene_id);
void play_send_input(Play *play, InputKey key);
void play_draw(Play *play, Display *display);

#endif
