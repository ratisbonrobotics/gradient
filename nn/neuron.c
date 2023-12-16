#include <stdlib.h>
#include "neuron.h"
#include "value.h"
#include "operation.h"

struct neuron_
{
    unsigned int input_size;
    value *w;
    value b;

    value *xiwi;
    value sigma_xiwi;
    value sigma_xiwi_bias;
    value y;
};

neuron Neuron(neuron *children, unsigned int input_size, operation act, operation act_deriv)
{
    neuron n = malloc(sizeof(struct neuron_));
    n->input_size = input_size;

    for (unsigned int i = 0; i < input_size; i++)
    {
        n->w[i] = Value(NULL, NULL, op_none, op_derivative_none);
        n->xiwi[i] = Value(getY(children[i]), n->w[i], op_mult, op_derivative_mult);
    }

    for (unsigned int i = 0; i < input_size; i++)
    {
        n->sigma_xiwi = Value(n->sigma_xiwi, n->xiwi[i], op_add, op_derivative_add);
    }

    n->b = Value(NULL, NULL, NULL, NULL);
    n->sigma_xiwi_bias = Value(n->sigma_xiwi, n->b, op_add, op_derivative_add);

    n->y = Value(n->sigma_xiwi_bias, NULL, act, act_deriv);

    return n;
}

value getY(neuron n)
{
    if (n == NULL)
    {
        return NULL;
    }
    else
    {
        return n->y;
    }
}

value *getW(neuron n)
{
    if (n == NULL)
    {
        return NULL;
    }
    else
    {
        return n->w;
    }
}

value getB(neuron n)
{
    if (n == NULL)
    {
        return NULL;
    }
    else
    {
        return n->b;
    }
}

unsigned int getInputSize(neuron n)
{
    if (n == NULL)
    {
        return 0;
    }
    else
    {
        return n->input_size;
    }
}

void forward(neuron n)
{
    forward_value(n->y);
}

void backward(neuron n)
{
    backward_value(n->y);
}
