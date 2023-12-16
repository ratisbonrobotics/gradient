#include "value.h"
#include <stdlib.h>

struct value_
{
    double data;
    double grad;
    value child_left;
    value child_right;
    pass_function forward;  // sets data
    pass_function backward; // set gradient for children
};

value Value(value child_left, value child_right, pass_function forward, pass_function backward)
{
    value v = malloc(sizeof(struct value_));
    v->child_left = child_left;
    v->child_right = child_right;
    v->forward = forward;
    v->backward = backward;
    return v;
}

value getChildLeft(value v)
{
    return v->child_left;
}

value getChildRight(value v)
{
    return v->child_right;
}

value setData(value v, double data)
{
    v->data = data;
}

double getData(value v)
{
    return v->data;
}

value setGrad(value v, double grad)
{
    v->grad = grad;
}

double getGrad(value v)
{
    return v->grad;
}

pass_function getForward(value v)
{
    return v->forward;
}

pass_function getBackward(value v)
{
    return v->backward;
}
