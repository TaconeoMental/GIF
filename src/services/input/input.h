#ifndef OGF_INPUT
#define OGF_INPUT

#include <inttypes.h>

#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>

#define BUTTON_ANALOG_PIN 12
#define ANALOG_VALUE_MARGIN 100

#define INPUT_LEFT_EVENT (1 << 0)
#define INPUT_OK_EVENT (1 << 1)
#define INPUT_RIGHT_EVENT (1 << 2)
#define BUTTON_MASK (INPUT_LEFT_EVENT | INPUT_RIGHT_EVENT | INPUT_OK_EVENT)

enum InputKey
{
    InputKeyLeft,
    InputKeyOk,
    InputKeyRight,
    InputKeyBack,

    // Valor especial, no tocar ni mover
    InputKeyNotPressed,
};

struct InputButton
{
    InputKey key;
    uint16_t analog_value;
    char name[10];
};

struct Input
{
    InputButton *buttons;
    uint16_t analog_pin;
    QueueHandle_t event_queue;
};

#endif
