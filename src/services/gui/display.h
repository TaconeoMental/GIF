#ifndef GUI_DISPLAY_H
#define GUI_DISPLAY_H

#include <U8g2lib.h>

// Pines i2c de la pantalla OLED
#define GUI_DISPLAY_SDA 21
#define GUI_DISPLAY_SCL 22

#define U8G2_TYPE U8G2_SH1106_128X64_NONAME_F_HW_I2C

/* Colores para la pantalla OLED */
enum Colour
{
    ColourWhite = 0x00,
    ColourBlack = 0x01,
};

enum Font
{
    FontPrimary,
    FontSecondary,
};

enum Alignment
{
    AlignmentLeft,
    AlignmentRight,
    AlignmentTop,
    AlignmentBottom,
    AlignmentCenter
};

struct DisplayFrame
{
    uint8_t x;
    uint8_t y;
    uint8_t width;
    uint8_t height;
};

/* Estructura prncipal del display OLED
 *
 * El display en sí tiene un ancho y un alto, pero podemos definir un "frame".
 * Este corresponde a la parte de la pantalla en la que se va a dibujar cuando
 * se llame a todas las funciones principales. El frame se comporta como si ese
 * fuera todo el display, es decir, su esquina superior izquierda se transforma
 * en el nuevo origen.
 *
 * Display:
 *                   v
 *             +-----------------------------------+ ~
 *             |                                   | y_t
 *    Origen > |     +-----------------------+     | ~
 *             |     |                       |     |
 *             |     |                       |     |
 *             |     |         FRAME         |     |
 *             |     |                       |     |
 *             |     |                       |     |
 *             |     +-----------------------+     | ~
 *             |                                   | y_b
 *             +-----------------------------------+ ~
 *             [ x_l ]                       [ x_r ]
 * */
struct Display
{
    U8G2_TYPE u8g2i;
    uint8_t width;
    uint8_t height;

    DisplayFrame frame;

    Colour current_colour;
};

/* Inicializar Display */
void display_init(Display *display, uint8_t width, uint8_t height);

/* Configurar el frame (Area máxima en la que se trabaja) */
void display_set_frame(Display *display, DisplayFrame frame);

/* Commit el buffer y dibujarlo */
void display_commit(Display *display);

/* Devuelve todo a la configuración predeterminada */
void display_reset(Display *display);

/* Borra la pantalla */
void display_clear(Display *display);

/* Devuelve el ancho del área dibujable */
uint8_t display_get_frame_width(Display *display);

/* Devuelve la altura del área dibujable */
uint8_t display_get_frame_height(Display *display);

/* Devuelve una estructura con las variables que describen al área dibujable */
DisplayFrame display_get_frame(Display *display);

/* Cofigura el color para dibujar */
void display_set_colour(Display *display, Colour colour);

/* Conmuta el color con el que se está dibujando */
void display_invert_colour(Display *display);

/* Configura el tipo de fuente a usar */
void display_set_font(Display *display, Font font);

/* Imprime una cadena de texto en (x, y) */
void display_draw_str(Display* canvas, char *str, uint8_t x, uint8_t y);

/* Imprime una cadena de texto alineada en la pantalla */
void display_draw_str_aligned(Display *display, char *str, Alignment h_align, Alignment v_align);

/* Dibuja un pixel en (x, y) */
void display_draw_pixel(Display* display, uint8_t x, uint8_t y);

/* Dibuja una línea con entre (x1, y1) y (x2, y2) */
void display_draw_line(Display* display, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);

/* Dibuja un cuadrilátero con su vértice superior izquierdo en (x, y) */
void display_draw_box(Display* display, uint8_t x, uint8_t y, uint8_t width, uint8_t height);

/* Dibuja un cuadrilátero alineado */
void display_draw_box_aligned(Display *display,
                              uint8_t width,
                              uint8_t height,
                              Alignment h_align,
                              Alignment v_align);

/* Dibuja un cuadro (El borde de un cuadrilátero) */
void display_draw_frame(Display* display, uint8_t x, uint8_t y, uint8_t width, uint8_t height);

/* Dibuja un cuadro alineado */
void display_draw_frame_aligned(Display *display,
                              uint8_t width,
                              uint8_t height,
                              Alignment h_align,
                              Alignment v_align);

// TODO
/*
void display_draw_circle(Display* canvas, uint8_t x, uint8_t y, uint8_t r);
void display_draw_disc(Display* canvas, uint8_t x, uint8_t y, uint8_t r);

void display_draw_rbox(
    Display* canvas,
    uint8_t x,
    uint8_t y,
    uint8_t width,
    uint8_t height,
    uint8_t radius);

void display_draw_rframe(
    Display* canvas,
    uint8_t x,
    uint8_t y,
    uint8_t width,
    uint8_t height,
    uint8_t radius);
*/

#endif
