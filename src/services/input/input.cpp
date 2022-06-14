#include "input.h"

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/timers.h>
//#include <freertos/event_groups.h>

#include "mini_log.h"

Input input_g;

const InputButton OGF_BUTTONS[] =
{
    {InputKeyLeft, 0, "LEFT"},
    {InputKeyOk, 260, "OK"},
    {InputKeyRight, 640, "RIGHT"},
};
const uint8_t OGF_BUTTON_COUNT = sizeof(OGF_BUTTONS) / sizeof(InputButton);

static void input_init(Input *input)
{
    input->buttons = (InputButton *) pvPortMalloc(sizeof(OGF_BUTTONS));
    memcpy(input->buttons, MINIGUI_BUTTONS, sizeof(OGF_BUTTONS));
    //input->flags_event_group = xEventGroupCreate();
    input->analog_pin = BUTTON_ANALOG_PIN;
    input->event_queue = xQueueCreate(5, sizeof(InputKey));
}

// Esto perfectamente podría ser un atributo de InputButton...
static EventBits_t bitmask_from_key(InputKey key)
{
    switch (key)
    {
    case InputKeyLeft:
        return INPUT_LEFT_EVENT;
    case InputKeyOk:
        return INPUT_OK_EVENT;
    case InputKeyRight:
        return INPUT_RIGHT_EVENT;
    }
}

// Podría ser un macro, pero no me importa porque como torta
static bool acceptable_analog_value(uint16_t read_a_value, uint16_t a_value)
{
    return (read_a_value >= a_value - ANALOG_VALUE_MARGIN) &&
           (read_a_value <= a_value + ANALOG_VALUE_MARGIN);
}

void input_service_init()
{
    input_init(&input_g);
}

void input_service(void *pvParams)
{
    uint16_t analog_value;
    InputButton button;
    InputKey last_key = InputKeyNotPressed;
    //EventBits_t event_bit_mask;
    bool found;

    TickType_t last_wake_time = xTaskGetTickCount();

    while (1)
    {
        analog_value = analogRead(input_g.analog_pin);

        found = false;
        for (uint8_t i = 0; i < MINIGUI_BUTTON_COUNT; i++)
        {
            button = input_g.buttons[i];
            if (acceptable_analog_value(analog_value, button.analog_value))
            {
                found = true;
                if (button.key != last_key)
                {
                    MLOG_D("New '%s' button press (AV: %d, AV read: %d)",
                            button.name,
                            button.analog_value,
                            analog_value);

                    /*
                    xEventGroupSetBits(input_g.flags_event_group,
                                       bitmask_from_key(button.key));
                    */

                    BaseType_t xStatus = xQueueSendToBack(input_g.event_queue, &button.key, portMAX_DELAY);
                    if (xStatus != pdPASS)
                    {
                        MLOG_W("Could not send %d to the queue", button.key);
                    }

                    last_key = button.key;
                    break;
                }
            }
        }
        if (!found)
        {
            last_key = InputKeyNotPressed;
        }
        // Vamos a ejecutar esta task cada 200 ms, constantemente
        vTaskDelayUntil(&last_wake_time, 200 / portTICK_PERIOD_MS);
    }
    MLOG_E("Should never get here");
}
