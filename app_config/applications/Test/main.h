#define VIEW_MODEL
Label title_1;
Label title_2;

#define VIEW_INIT
label_init_text(MODEL(title_1), "EJEMPLO!");
label_init_text(MODEL(title_2), ":D!");
label_grid(MODEL(title_1), MAIN_FRAME, 0, 1, GIF_NO_PADDING);
label_grid(MODEL(title2), MAIN_FRAME, 1, 0, GIF_NO_PADDING);

#define VIEW_INPUT_HANDLER
OK_GOTO(Second)
