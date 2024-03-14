#include <math.h>
#include <stdlib.h>

//#define EGFX_IMPLEMENTATION
#include "egfx.h"

#define HEIGHT 800
#define WIDTH 800

int main(void)
{
    eCanvas can = eGetCanvas(WIDTH, HEIGHT, 0x00000000);

    V2 polygon[] = {
        (V2) { WIDTH >> 1, 0 },
        (V2) { WIDTH, HEIGHT >> 1 },
        (V2) { WIDTH >> 1, HEIGHT },
        (V2) { 0, HEIGHT >> 1 }
    };

    int G_WIDTH = 80;
    int G_HEIGHT = 80;
    int G_SIZE = G_WIDTH * G_HEIGHT;

    int T_WIDTH = WIDTH / G_WIDTH;
    int T_HEIGHT = HEIGHT / G_HEIGHT;
 
    float x_step = 1.0 / G_WIDTH; 
    float y_step = 1.0 / G_HEIGHT; 

    uint32_t a = 0xff0000ff;
    uint32_t b = 0xffff0000;
    uint32_t c = 0xff00ff00;
    uint32_t d = 0xffffff00;

    div_t pos;
    for (int i = 0; i < G_SIZE; ++i){
        pos = div(i, G_WIDTH);

        uint32_t top = eLerpColor(a, b, x_step * pos.rem);
        uint32_t bottom = eLerpColor(c, d, x_step * pos.rem);

        eDrawRectangle(&can, T_WIDTH * pos.rem, T_HEIGHT * pos.quot, T_WIDTH, T_HEIGHT, eLerpColor(top, bottom, y_step * pos.quot));
    }

    //eInvertCircleBorder(can, WIDTH >> 1, HEIGHT >> 1, (HEIGHT - 50) >> 1, 100);
    eInvertCircle(&can, WIDTH >> 1, HEIGHT >> 1, (HEIGHT - 50) >> 1);
    eInvertCircle(&can, WIDTH >> 1, HEIGHT >> 1, ((HEIGHT - 50) >> 1) - 100);

    int rect_pos = 125;
    int rect_size = WIDTH - 2 * rect_pos;

    eInvertRectangle(&can, rect_pos, rect_pos, rect_size, rect_size);

    eFillPolygon(&can, polygon, 4, 0xffff0000);

    eWriteCanvasToPpm(&can, "test.ppm");
    eFreeCanvas(&can);
    
    return 0;
}
