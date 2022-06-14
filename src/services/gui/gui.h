#ifndef GUI_H
#define GUI_H

#include "display.h"
#include "theater.h"

// Pantalla
#define GUI_DISPLAY_WIDTH 128
#define GUI_DISPLAY_HEIGHT 64

// Status Bar
#define GUI_STATUS_BAR_X 0
#define GUI_STATUS_BAR_Y 0
#define GUI_STATUS_BAR_WIDTH GUI_DISPLAY_WIDTH
#define GUI_STATUS_BAR_HEIGHT 15

// Ventana "utilizable"
#define GUI_WINDOW_X GUI_STATUS_BAR_X
#define GUI_WINDOW_Y GUI_STATUS_BAR_Y
#define GUI_WINDOW_WIDTH GUI_DISPLAY_WIDTH
#define GUI_WINDOW_HEIGHT (GUI_DISPLAY_HEIGHT - GUI_STATUS_BAR_HEIGHT)

//#define GUI_SCENE_STACK_SIZE 5

struct Gui
{
    Display *display;
    Theater *theater;
};

#endif
