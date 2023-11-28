#include "font.h"
#include "primitives.h"

void draw_char(unsigned char *arr, int width, int height, int x, int y, unsigned char character, unsigned char color, int scale)
{
    scale *= 10;

    switch (character)
    {
    case 'a':
        drawCircle(arr, width, height, x, y + scale / 2, scale / 2, color, 2);
        drawLine(arr, width, height, x + scale / 2, y, x + scale / 2, y + scale, color, 2);
        break;
    case 'b':
        drawCircle(arr, width, height, x, y + scale / 2, scale / 2, color, 2);
        drawLine(arr, width, height, x - scale / 2, y - scale, x - scale / 2, y + scale, color, 2);
        break;
    case 'c':
        drawArc(arr, width, height, x, y + scale / 2, scale / 2, 30, 340, color, 2);
        break;
    case 'd':
        drawCircle(arr, width, height, x, y + scale / 2, scale / 2, color, 2);
        drawLine(arr, width, height, x + scale / 2, y - scale, x + scale / 2, y + scale, color, 2);
        break;
    case 'e':
        drawArc(arr, width, height, x, y, scale, 40, 360, color, 2);
        drawLine(arr, width, height, x - scale, y, x + scale, y, color, 2);
        break;
    case 'f':
        drawLine(arr, width, height, x, y - scale * 2, x, y + scale, color, 2);
        drawLine(arr, width, height, x - scale / 2, y, x + scale / 2, y, color, 2);
        drawArc(arr, width, height, x + scale / 4, y - scale * 2, scale / 4, 180, 270, color, 2);
        drawLine(arr, width, height, x + scale / 4, y - scale * 2 - scale / 4, x + scale / 2, y - scale * 2 - scale / 4, color, 2);
        break;
    case 'g':
        drawCircle(arr, width, height, x, y, scale - scale / 3, color, 2);
        drawLine(arr, width, height, x + scale - scale / 3, y, x + scale - scale / 3, y + scale * 2, color, 2);
        drawArc(arr, width, height, x, y + scale * 2, scale - scale / 3, 0, 180, color, 2);
        break;
    case 'h':
        drawLine(arr, width, height, x, y - scale * 2, x, y + scale, color, 2);
        drawLine(arr, width, height, x + scale, y, x + scale, y + scale, color, 2);
        drawLine(arr, width, height, x, y, x + scale, y, color, 2);
        break;
    case 'i':
        drawLine(arr, width, height, x, y, x, y + scale, color, 2);
        drawCircle(arr, width, height, x, y - scale, scale / 20, color, 2);
        break;
    case 'j':
        drawLine(arr, width, height, x, y, x, y + scale * 2, color, 2);
        drawCircle(arr, width, height, x, y - scale, scale / 20, color, 2);
        drawLine(arr, width, height, x - scale / 2, y + scale * 2, x, y + scale * 2, color, 2);
        break;
    case 'k':
        drawLine(arr, width, height, x, y - scale * 2, x, y + scale, color, 2);
        drawLine(arr, width, height, x, y, x + scale, y - scale, color, 2);
        drawLine(arr, width, height, x, y, x + scale, y + scale, color, 2);
        break;
    case 'l':
        drawLine(arr, width, height, x, y - scale * 2, x, y + scale, color, 2);
        break;
    case 'm':
        drawLine(arr, width, height, x, y, x, y + scale, color, 2);
        drawLine(arr, width, height, x + scale, y, x + scale, y + scale, color, 2);
        drawLine(arr, width, height, x + scale * 2, y, x + scale * 2, y + scale, color, 2);
        drawLine(arr, width, height, x, y, x + scale * 2, y, color, 2);
        break;
    case 'n':
        drawLine(arr, width, height, x, y, x, y + scale, color, 2);
        drawLine(arr, width, height, x + scale, y, x + scale, y + scale, color, 2);
        drawLine(arr, width, height, x, y, x + scale, y, color, 2);
        break;
    case 'o':
        drawCircle(arr, width, height, x, y + scale / 2, scale / 2, color, 2);
        break;
    case 'p':
        drawCircle(arr, width, height, x, y + scale / 2, scale / 2, color, 2);
        drawLine(arr, width, height, x - scale / 2, y, x - scale / 2, y + scale * 2, color, 2);
        break;
    case 'q':
        drawCircle(arr, width, height, x, y + scale / 2, scale / 2, color, 2);
        drawLine(arr, width, height, x + scale / 2, y, x + scale / 2, y + scale * 2, color, 2);
        break;
    case 'r':
        drawLine(arr, width, height, x - scale / 2, y, x - scale / 2, y + scale, color, 2);
        drawLine(arr, width, height, x - scale / 2, y, x + scale / 2, y, color, 2);
        break;
    case 's':
        drawArc(arr, width, height, x, y - scale / 3 + scale / 2, scale / 3, 90, 360, color, 2);
        drawArc(arr, width, height, x, y + scale / 3 + scale / 2, scale / 3, 270, 520, color, 2);
        break;
    case 't':
        drawLine(arr, width, height, x, y - scale - scale / 2, x, y + scale - scale / 4, color, 2);
        drawLine(arr, width, height, x - scale / 2, y, x + scale / 2, y, color, 2);
        drawArc(arr, width, height, x + scale / 2, y + scale / 2 + scale / 4, scale / 2, 70, 180, color, 2);
        break;
    case 'u':
        drawLine(arr, width, height, x, y, x, y + scale, color, 2);
        drawLine(arr, width, height, x + scale, y, x + scale, y + scale, color, 2);
        drawLine(arr, width, height, x, y + scale, x + scale, y + scale, color, 2);
        break;
    case 'v':
        drawLine(arr, width, height, x, y, x + scale / 2, y + scale, color, 2);
        drawLine(arr, width, height, x + scale, y, x + scale / 2, y + scale, color, 2);
        break;
    case 'w':
        drawLine(arr, width, height, x, y, x + scale / 3, y + scale, color, 2);
        drawLine(arr, width, height, x + scale / 3, y + scale, x + 2 * scale / 3, y, color, 2);
        drawLine(arr, width, height, x + 2 * scale / 3, y, x + scale, y + scale, color, 2);
        drawLine(arr, width, height, x + scale, y + scale, x + 4 * scale / 3, y, color, 2);
        break;
    case 'x':
        drawLine(arr, width, height, x, y, x + scale, y + scale, color, 2);
        drawLine(arr, width, height, x + scale, y, x, y + scale, color, 2);
        break;
    case 'y':
        drawLine(arr, width, height, x, y, x + scale / 2, y + scale, color, 2);
        drawLine(arr, width, height, x + scale, y, x + scale / 2, y + scale, color, 2);
        drawLine(arr, width, height, x + scale / 2, y + scale, x + scale / 2, (int)(y + scale * 1.5), color, 2);
        break;
    case 'z':
        drawLine(arr, width, height, x, y, x + scale, y, color, 2);
        drawLine(arr, width, height, x + scale, y, x, y + scale, color, 2);
        drawLine(arr, width, height, x, y + scale, x + scale, y + scale, color, 2);
        break;
    default:
        break;
    }
}