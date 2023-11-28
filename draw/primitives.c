#include "primitives.h"
#include <math.h>

#define PI 3.14159265358979323846
#define ABS(x) ((x) < 0 ? -(x) : (x))

static void setPixel(unsigned char *arr, int width, int height, int x, int y, unsigned char color)
{
    if (x >= 0 && x < width && y >= 0 && y < height)
    {
        arr[y * width + x] = color;
    }
}

/* Bresenham's line algorithm */
void drawLine(unsigned char *arr, int width, int height,
              int x0, int y0, int x1, int y1,
              unsigned char color, int thickness)
{
    int dx = ABS(x1 - x0);
    int dy = ABS(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (1)
    {
        setPixel(arr, width, height, x0, y0, color);

        // Draw thickness around the central line
        for (int t = 1; t <= thickness / 2; t++)
        {
            setPixel(arr, width, height, x0 + t, y0, color);
            setPixel(arr, width, height, x0 - t, y0, color);
            setPixel(arr, width, height, x0, y0 + t, color);
            setPixel(arr, width, height, x0, y0 - t, color);
        }

        if (x0 == x1 && y0 == y1)
            break;

        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

void drawCircle(unsigned char *arr, int width, int height, int centerX, int centerY, int radius, unsigned char color, int thickness)
{
    drawArc(arr, width, height, centerX, centerY, radius, 0, 360, color, thickness);
}

void drawArc(unsigned char *arr, int width, int height, int x, int y, int radius, int startAngle, int endAngle, unsigned char color, int thickness)
{
    int dx, dy, tx, ty;

    for (int r = 0; r < thickness + (thickness / 2); ++r)
    {
        for (double angle = startAngle; angle <= endAngle; angle += 0.01)
        {
            // Convert angle to radians
            double angleRadians = angle * (PI / 180.0);

            // Calculate sine and cosine values using math library functions
            dx = (int)(cos(angleRadians) * (radius + r));
            dy = (int)(sin(angleRadians) * (radius + r));

            // Calculate the target pixel
            tx = x + dx;
            ty = y + dy;

            setPixel(arr, width, height, tx, ty, color);
        }
    }
}