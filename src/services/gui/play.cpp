#include "play.h"

#include "common.h"

Play *play_alloc()
{
    Play *play = (Play *) pvPortMalloc(sizeof(Play));
    play->current_scene_id = 0;
    play->event_queue = xQueueCreate(5, sizeof(InputKey));
    return play;
}

void play_free(Play *play)
{
    assert_ptr(play);
    free(play);
}

void play_set_context(Play *play, void *context)
{
    assert_ptr(play);
    assert_ptr(context);
    play->context = context;
}

void play_set_script_handlers(Play *play, const ScriptHandlers *handlers)
{
    assert_ptr(play);
    assert_ptr(handlers);
    play->script = handlers;
}

void play_next_scene(Play *play, uint8_t scene_id)
{
    assert_ptr(play);
    // TODO: Añadir un assert genérico?
    // assert(scene_id > 0);

    play->next_scene_id = scene_id;
}

void play_enter_scene(Play *play)
{
    assert_ptr(play);
    // on_enter_handler de la escena nueva
    play->script->on_enter_handlers[play->current_scene_id](play->context);
}

void play_switch_to_scene(Play *play, uint8_t scene_id)
{
    assert_ptr(play);

    // on_exit_handler de la escena actual
    play->script->on_exit_handlers[play->current_scene_id](play->context);

    if (play->next_scene_id == scene_id)
    {
        play->next_scene_id = 0;
    }
    play->current_scene_id = scene_id;

    play_enter_scene(play);
}

void play_send_input(Play *play, InputKey key)
{
    assert_ptr(play);
    play->script->on_input_handlers[play->current_scene_id](play->context);
}

void play_draw(Play *play, Display *display)
{
    assert_ptr(play);
    play->script->draw_callbacks[play->current_scene_id](display);
}

void play_start(Play *play)
{
    assert_ptr(play);

    play_enter_scene(play);
    InputKey input_key;
    while (1)
    {
        if (xQueueReceive(play->event_queue,
                    &input_key,
                    portMAX_DELAY) == pdPASS)
        {
            play_send_input(play, input_key);
        }
    }
}
