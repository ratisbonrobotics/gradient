#include "operation.h"
#include <math.h>
#include <stdlib.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double op_none(double x, double _unused)
{
    (void)_unused;
    return x;
}

double op_derivative_none(double _unused, double grad)
{
    (void)_unused;
    (void)grad;
    return 0;
}

double op_add(double d1, double d2)
{
    return d1 + d2;
}

double op_derivative_add(double _unused, double grad)
{
    (void)_unused;
    return grad;
}

double op_mult(double d1, double d2)
{
    return d1 * d2;
}

double op_derivative_mult(double x, double grad)
{
    return x * grad;
}

double op_sigmoid(double x, double _unused)
{
    (void)_unused;
    return 1 / (1 + exp(-x));
}

double op_derivative_sigmoid(double x, double grad)
{
    return (1 - x) * x * grad;
}

double op_tanh(double x, double _unused)
{
    (void)_unused;
    return tanh(x);
}

double op_derivative_tanh(double x, double grad)
{
    return (1 - pow(x, 2)) * grad;
}

double op_gelu(double x, double _unused)
{
    (void)_unused;
    return 0.5 * x * (1 + tanh(sqrt(2 / M_PI) * (x + 0.044715 * pow(x, 3))));
}

double op_derivative_gelu(double x, double grad)
{
    double tanh_term = tanh(sqrt(2 / M_PI) * (x + 0.044715 * pow(x, 3)));
    double derivative = 0.5 * tanh_term + (0.5 * x * (1 + tanh_term)) * (1 - pow(tanh_term, 2)) * (sqrt(2 / M_PI) + 0.134145 * pow(x, 2));
    return derivative * grad;
}
