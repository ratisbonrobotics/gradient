#include "value.h"
#include <stdlib.h>

struct value_
{
    double data;
    double grad;
    value child_left;
    value child_right;
    pass_function operation;
    pass_function operation_derivative;
};

value Value(value child_left, value child_right, pass_function operation, pass_function operation_derivative)
{
    value v = malloc(sizeof(struct value_));
    v->child_left = child_left;
    v->child_right = child_right;
    v->operation = operation;
    v->operation_derivative = operation_derivative;
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
    return v->operation;
}

pass_function getBackward(value v)
{
    return v->operation_derivative;
}

void forward_value(value v)
{
    if (v->child_left != NULL)
    {
        forward_value(v->child_left);
    }
    if (v->child_right != NULL)
    {
        forward_value(v->child_right);
    }
    v->operation(v);
}

void backward_value(value v)
{
    if (v->child_left != NULL)
    {
        v->operation_derivative(getChildLeft(v));
        backward_value(v->child_left);
    }
    if (v->child_right != NULL)
    {
        v->operation_derivative(getRightLeft(v));
        backward_value(v->child_right);
    }
}