#include "input.h"

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/timers.h>

#include "mini_log.h"
#include "common.h"
#include "resource.h"
#include "services/gui/gui.h"

const InputButton OGF_BUTTONS[] =
{
    {InputKeyLeft, 0, "LEFT"},
    {InputKeyOk, 260, "OK"},
    {InputKeyRight, 640, "RIGHT"},
};
const uint8_t OGF_BUTTON_COUNT = COUNT_OF(OGF_BUTTONS);

static Input *input_alloc()
{
    Input *input = (Input *) pvPortMalloc(sizeof(Input));
    input->buttons = (InputButton *) pvPortMalloc(sizeof(OGF_BUTTONS));
    memcpy(input->buttons, OGF_BUTTONS, sizeof(OGF_BUTTONS));
    input->analog_pin = BUTTON_ANALOG_PIN;
    input->event_queue = xQueueCreate(5, sizeof(InputKey));
    return input;
}

// Podría ser un macro, pero no me importa porque como torta
static bool acceptable_analog_value(uint16_t read_a_value, uint16_t a_value)
{
    return (read_a_value >= a_value - ANALOG_VALUE_MARGIN) &&
           (read_a_value <= a_value + ANALOG_VALUE_MARGIN);
}

void input_service(void *pvParams)
{
    Input *input = input_alloc();
    ogf_resource_create("input", input);

    Gui *gui = (Gui *) ogf_resource_open("gui");

    uint16_t analog_value;
    InputButton button;
    InputKey last_key = InputKeyNotPressed;
    bool found;

    TickType_t last_wake_time = xTaskGetTickCount();

    while (1)
    {
        analog_value = analogRead(input->analog_pin);

        found = false;
        for (uint8_t i = 0; i < OGF_BUTTON_COUNT; i++)
        {
            button = input->buttons[i];
            if (acceptable_analog_value(analog_value, button.analog_value))
            {
                found = true;
                if (button.key != last_key)
                {
                    MLOG_D("New '%s' button press (AV: %d, AV read: %d)",
                            button.name,
                            button.analog_value,
                            analog_value);

                    BaseType_t xStatus = xQueueSendToBack(input->event_queue, &button.key, portMAX_DELAY);
                    if (xStatus != pdPASS)
                    {
                        MLOG_W("Could not send %d to the queue", button.key);
                    }
                    else
                    {
                        xEventGroupSetBits(gui->flags_event_group, GUI_FLAG_INPUT);
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
