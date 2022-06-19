#include "theater.h"

#include "mini_log.h"
#include "common.h"

Theater *theater_alloc(Display *display)
{
    Theater *theater = (Theater *) pvPortMalloc(sizeof(Theater));
    theater->play_count = 0;
    theater->display = display;
    return theater;
}

void theater_send_input(Theater *theater, InputKey key)
{
    assert_ptr(theater);
    play_send_input(theater->current_play, key);
}

Play *theater_get_current_play(Theater *theater)
{
    assert_ptr(theater);
    return  theater->current_play;
}

void theater_push_play(Theater *theater, Play *play)
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
}
