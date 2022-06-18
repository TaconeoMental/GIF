#include "theater.h"

#include "mini_log.h"

void theater_init(Theater *theater)
{
    assert_ptr(theater);
    // TODO: Init con una vista vacía
}

void theater_send_input(Theater *theater, InputKey key)
{
    assert_ptr(theater);

    //theater->current_view->input_callback();
    play_send_input(theater->current_play, key);
}

/*
void theater_draw(Theater *theater)
{
    assert_ptr(theater);
    theater->current_play
}
*/

void theater_start_play(Theater *theater, Play *play)
{
    assert_ptr(theater);
    assert_ptr(play);

    if (theater->play_count == MAX_APPLICATION_COUNT)
    {
        MLOG_E("Arreglo de aplicaciones lleno!");
        return;
    }
    theater->plays[theater->play_count++] = play;
    theater->current_play = play;
    play_enter_scene(play);
}
