#include "display.h"

#define u8g2p(display) (display->u8g2i)

// Helper para alinear objetos
static void align_point(Display *display,
                        uint8_t *x,
                        uint8_t *y,
                        uint8_t w,
                        uint8_t h,
                        Alignment h_align,
                        Alignment v_align)
{
    switch (h_align)
    {
    case AlignmentLeft:
        break;

    case AlignmentCenter:
        *x = (uint8_t)((display_get_frame_width(display) - w) / 2);
        break;

    case AlignmentRight:
        *x = display_get_frame_width(display) - w;
        break;
    }

    switch (v_align)
    {
    case AlignmentTop:
        *y = 0;
        break;

    case AlignmentCenter:
        *y = (uint8_t)((display_get_frame_height(display) - h) / 2);
        break;

    case AlignmentBottom:
        *y = display_get_frame_height(display) - h;
        break;
    }
}

void display_init(Display *display, uint8_t width, uint8_t height)
{
    U8G2_TYPE u8g2_v(U8G2_R0, GUI_DISPLAY_SCL, GUI_DISPLAY_SDA, U8X8_PIN_NONE);

    u8g2p(display) = u8g2_v;
    u8g2p(display).begin();

    display->width = width;
    display->height = height;

    // DEBUG!!
    //u8g2p(display).setDisplayRotation(U8G2_R2);

    display->current_colour = ColourWhite;
    display_set_font(display, FontPrimary);
    display_set_frame(display, 0, 0, 0, 0);
}

void display_set_frame(Display *display,
                       uint8_t x_roffset,
                       uint8_t x_loffset,
                       uint8_t y_toffset,
                       uint8_t y_boffset)
{
    display->x_roffset = x_roffset;
    display->x_loffset = x_loffset;
    display->y_toffset = y_toffset;
    display->y_boffset = y_boffset;
}

void display_commit(Display *display)
{
    u8g2p(display).sendBuffer();
}

void display_reset(Display *display)
{
    display_clear(display);
    display_set_colour(display, ColourBlack);
    display_set_font(display, FontSecondary);
    display_set_frame(display, 0, 0, 0, 0);
}

void display_clear(Display *display)
{
    u8g2p(display).clear();
}

uint8_t display_get_frame_width(Display *display)
{
    return display->width - display->x_loffset - display->x_roffset;
}

uint8_t display_get_frame_height(Display *display)
{
    return display->height - display->y_boffset - display->y_toffset;
}

void display_set_colour(Display *display, Colour colour)
{
    u8g2p(display).setFontMode(0);
    u8g2p(display).setDrawColor((uint8_t)colour);
}

void display_invert_colour(Display *display)
{
    // Trucherío B)
    display->current_colour = (Colour)!display->current_colour;
    display_set_colour(display, display->current_colour);
}

void display_set_font(Display *display, Font font)
{
    u8g2p(display).setFontMode(1);
    if (font == FontPrimary)
    {
        u8g2p(display).setFont(u8g2_font_helvB08_tr);
    }
    else if (font == FontSecondary)
    {
        u8g2p(display).setFont(u8g2_font_haxrcorp4089_tr);
    }
}

void display_draw_str(Display* display, char *str, uint8_t x, uint8_t y)
{
    u8g2p(display).drawStr(x + display->x_loffset, y + display->y_toffset, str);
}

void display_draw_str_aligned(Display *display, char *str, Alignment h_align, Alignment v_align)
{
    uint8_t x = 0;
    uint8_t y = 0;

    // El +1 es por cómo está definida la función "U8G2::setFontPosTop", que
    // pone el origen del font 1 pixel más arriba que el glyph más alto.
    align_point(display,
                &x, &y,
                u8g2p(display).getStrWidth(str), u8g2p(display).getAscent() + 1,
                h_align, v_align);

    u8g2p(display).setFontPosTop();
    display_draw_str(display, str, x, y);

    // Devolvemos el punto de referencia de los fonts para que el
    // comportamiento de otras funciones no cambie
    u8g2p(display).setFontPosBottom();
}

void display_draw_pixel(Display* display, uint8_t x, uint8_t y)
{
    x += display->x_loffset;
    y += display->y_toffset;
    u8g2p(display).drawPixel(x, y);
}

void display_draw_line(Display* display, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
    x1 += display->x_loffset;
    y1 += display->y_toffset;
    x2 += display->x_loffset;
    y2 += display->y_toffset;

    u8g2p(display).drawLine(x1, y1, x2, y2);
}

void display_draw_box(Display* display, uint8_t x, uint8_t y, uint8_t width, uint8_t height)
{
    x += display->x_loffset;
    y += display->y_toffset;
    u8g2p(display).drawBox(x, y, width, height);
}

void display_draw_box_aligned(Display *display,
                              uint8_t width,
                              uint8_t height,
                              Alignment h_align,
                              Alignment v_align)
{
    uint8_t x = 0;
    uint8_t y = 0;

    align_point(display, &x, &y, width, height, h_align, v_align);
    display_draw_box(display, x, y, width, height);
}

void display_draw_frame(Display* display, uint8_t x, uint8_t y, uint8_t width, uint8_t height)
{
    x += display->x_loffset;
    y += display->y_toffset;
    u8g2p(display).drawFrame(x, y, width, height);
}

void display_draw_frame_aligned(Display *display,
                                uint8_t width,
                                uint8_t height,
                                Alignment h_align,
                                Alignment v_align)
{
    uint8_t x = 0;
    uint8_t y = 0;

    align_point(display, &x, &y, width, height, h_align, v_align);
    display_draw_frame(display, x, y, width, height);
}
