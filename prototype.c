#include "bmp.h"
#include "font.h"
#include "primitives.h"

void circle_test(void)
{
    unsigned char arr[1000000] = {0};
    for (int i = 0; i < 1000000; i++)
    {
        arr[i] = 255;
    }
    drawCircle(arr, 1000, 1000, 500, 500, 300, 0, 10);
    save_8bit_color_bitmap(arr, 1000, 1000, "circle_test.bmp");
}

void font_test(void)
{
    unsigned char arr[1000000] = {0};
    for (int i = 0; i < 1000000; i++)
    {
        arr[i] = 255;
    }

    int x = 2500;
    int y = 400;

    for (int i = 'a'; i <= 'z'; i++)
    {
        draw_char(arr, x, y, 50 + (i - 'a') * 30, 50, (unsigned char)i, 0, 1);
    }
    for (int i = 'a'; i <= 'z'; i++)
    {
        draw_char(arr, x, y, 50 + (i - 'a') * 100, 250, (unsigned char)i, 0, 4);
    }
    save_8bit_color_bitmap(arr, (unsigned int)x, (unsigned int)y, "font_test.bmp");
}

int main_gradient(void)
{
    circle_test();
    font_test();
    return 0;
}