#pragma once

#define MODEL_NAME MODEL_S
#define MODEL_DEF struct MODEL_S
#define MODEL(x) model->custom_model.x

#define VIEW_INIT void custom_view_init
#define V_INIT_ARGS Frame *frame, MODEL_NAME *model

#define INPUT_HANDLER void custom_input_handler
#define INPUT_ARGS MODEL_NAME *model, InputKey key
