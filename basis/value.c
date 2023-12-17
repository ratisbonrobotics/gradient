#include "value.h"
#include <assert.h>
#include <stdlib.h>

struct value_
{
    double data;
    double grad;
    value child_left;
    value child_right;
    operation operation;
    operation operation_derivative;
};

value Value(value child_left, value child_right, operation op, operation op_derivative)
{
    value v = malloc(sizeof(struct value_));
    v->child_left = child_left;
    v->child_right = child_right;
    v->operation = op;
    v->operation_derivative = op_derivative;
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

void setData(value v, double data)
{
    v->data = data;
}

double getData(value v)
{
    return v->data;
}

void setGrad(value v, double grad)
{
    v->grad = grad;
}

double getGrad(value v)
{
    return v->grad;
}

operation getForward(value v)
{
    return v->operation;
}

operation getBackward(value v)
{
    return v->operation_derivative;
}

void forward_value(value v)
{
    double child_left_data = 0.0;
    double child_right_data = 0.0;

    if (v->child_left != NULL)
    {
        forward_value(v->child_left);
        child_left_data = v->child_left->data;
    }
    if (v->child_right != NULL)
    {
        forward_value(v->child_right);
        child_right_data = v->child_right->data;
    }

    setData(v, v->operation(child_left_data, child_right_data));
}

void backward_value(value v)
{
    if (v->child_left != NULL)
    {
        setGrad(v->child_left, v->child_left->grad + v->operation_derivative(v->child_left->data, v->grad));
        backward_value(v->child_left);
    }
    if (v->child_right != NULL)
    {
        setGrad(v->child_right, v->child_right->grad + v->operation_derivative(v->child_right->data, v->grad));
        backward_value(v->child_right);
    }
}

void update_value(value v, double learning_rate)
{
    if (v->child_left != NULL)
    {
        update_value(v->child_left, learning_rate);
    }
    if (v->child_right != NULL)
    {
        update_value(v->child_right, learning_rate);
    }
    setData(v, v->data - learning_rate * v->grad);
    setGrad(v, 0.0);
}

void free_value(value v)
{
    assert(v != NULL);
    if (v->child_left != NULL)
    {
        free_value(v->child_left);
    }
    if (v->child_right != NULL)
    {
        free_value(v->child_right);
    }

    free(v);
}
