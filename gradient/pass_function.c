#include "pass_function.h"
#include <math.h>
#include <stdlib.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void forward_empty(value v)
{
    setData(v, getData(v));
}

void backward_empty(value v)
{
    /* in this case v shouldnt have any children */
    assert(getChildLeft(v) == NULL && getChildRight(v) == NULL);
}

void forward_gelu(value v)
{
    value cl = getChildLeft(v);
    double x = getData(cl);
    double gelu = 0.5 * x * (1 + tanh(sqrt(2 / M_PI) * (x + 0.044715 * pow(x, 3))));
    setData(v, gelu);
}

void backward_gelu(value v)
{
    double x = getData(v);
    double tanh_term = tanh(sqrt(2 / M_PI) * (x + 0.044715 * pow(x, 3)));
    double derivative = 0.5 * tanh_term + (0.5 * x * (1 + tanh_term)) * (1 - pow(tanh_term, 2)) * (sqrt(2 / M_PI) + 0.134145 * pow(x, 2));
    setGrad(v, derivative * getGrad(v));
}

void forward_sigmoid(value v)
{
    value cl = getChildLeft(v);
    double x = getData(cl);
    setData(v, 1 / (1 + exp(-x)));
}

void backward_sigmoid(value v)
{
    double x = getData(v);
    setGrad(v, (1 - x) * x * getGrad(v));
}

void forward_tanh(value v)
{
    value cl = getChildLeft(v);
    double x = getData(cl);
    setData(v, tanh(x));
}

void backward_tanh(value v)
{
    double x = getData(v);
    setGrad(v, (1 - pow(x, 2)) * getGrad(v));
}

void forward_mult(value v)
{
    value cl = getChildLeft(v);
    value cr = getChildRight(v);
    setData(v, getData(cl) * getData(cr));
}

void backward_mult(value v)
{
    value cl = getChildLeft(v);
    value cr = getChildRight(v);
    setGrad(cl, getData(cr) * getGrad(v));
    setGrad(cr, getData(cl) * getGrad(v));
}

void forward_add(value v)
{
    value cl = getChildLeft(v);
    value cr = getChildRight(v);
    setData(v, getData(cl) + getData(cr));
}

void backward_add(value v)
{
    value cl = getChildLeft(v);
    value cr = getChildRight(v);
    setGrad(cl, getData(cl) * getGrad(v));
    setGrad(cr, getData(cr) * getGrad(v));
}
