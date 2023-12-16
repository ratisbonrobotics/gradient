#include <stdlib.h>
#include "neuron.h"
#include "value.h"
#include "pass_function.h"

void forward(neuron n)
{
    forward_value(n->y);
}

void backward(neuron n)
{
}

struct neuron_
{
    unsigned int input_size;
    value *x;
    value *w;
    value b;

    value *xiwi;
    value sigma_xiwi;
    value sigma_xiwi_bias;
    value y;
};

neuron Neuron(double *x, double *w, double b, unsigned int input_size, void (*act)(neuron), void (*deriv)(neuron))
{
    neuron n = malloc(sizeof(struct neuron_));
    n->input_size = input_size;
    n->x = malloc(sizeof(value) * input_size);
    n->w = malloc(sizeof(value) * input_size);

    for (unsigned int i = 0; i < input_size; i++)
    {
        n->x[i] = setData(Value(NULL, NULL, forward_empty, backward_empty), x[i]);
        n->w[i] = setData(Value(NULL, NULL, forward_empty, backward_empty), w[i]);
        n->xiwi[i] = Value(n->x[i], n->w[i], forward_mult, backward_mult);
    }

    for (unsigned int i = 0; i < input_size; i++)
    {
        n->sigma_xiwi = Value(n->sigma_xiwi, n->xiwi[i], forward_add, backward_add);
    }

    n->b = setData(Value(NULL, NULL, forward_empty, backward_empty), b);
    n->sigma_xiwi_bias = Value(n->sigma_xiwi, n->b, forward_add, backward_add);

    n->y = Value(n->sigma_xiwi_bias, NULL, act, deriv);

    return n;
}