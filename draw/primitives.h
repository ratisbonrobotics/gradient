#ifndef PRIMITIVES_H
#define PRIMITIVES_H

void drawCubicBezierCurve(unsigned char *arr, int width, int height,
                          int x0, int y0, int x1, int y1,
                          int x2, int y2, int x3, int y3,
                          unsigned char color, int thickness);

void drawLine(unsigned char *arr, int width, int height,
              int x0, int y0, int x1, int y1,
              unsigned char color, int thickness);

void drawCircle(unsigned char *arr, int width, int height, int centerX, int centerY, int radius, unsigned char color, int thickness);

void drawArc(unsigned char *arr, int width, int height, int x, int y, int radius, int startAngle, int endAngle, unsigned char color, int thickness);

#endif // PRIMITIVES_H
