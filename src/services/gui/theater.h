#ifndef GUI_THEATER_H
#define GUI_THEATER_H

#include "play.h"
#include "display.h"
#include "services/input/input.h"

#define MAX_APPLICATION_COUNT 5

struct Theater
{
    Display *display;
    Play *plays[MAX_APPLICATION_COUNT];
    uint8_t play_count;

    Play *current_play;
};

Theater *theater_alloc(Display *display);
void theater_send_input(Theater *theater, InputKey key);
void theater_push_play(Theater *theater, Play *play);

Play *theater_get_current_play(Theater *theater);

#endif
