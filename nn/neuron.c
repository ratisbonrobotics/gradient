#include <stdlib.h>
#include "neuron.h"
#include "value.h"

void forward(neuron n)
{
    value x1 = Value(NULL, NULL, forward_empty, backward_empty);
    value w1 = Value(NULL, NULL, forward_empty, backward_empty);
    value x1w1 = Value(x1, w1, forward_mult, backward_mult);

    value x2 = Value(NULL, NULL, forward_empty, backward_empty);
    value w2 = Value(NULL, NULL, forward_empty, backward_empty);
    value x2w2 = Value(x2, w2, forward_mult, backward_mult);

    value x1w1x2w2 = Value(x1w1, x2w2, forward_add, backward_add);
    value bias = Value(NULL, NULL, forward_empty, backward_empty);

    value x1w1x2w2bias = Value(x1w1x2w2, bias, forward_add, backward_add);
    value x1w1x2w2biasgelu = Value(x1w1x2w2bias, NULL, forward_gelu, backward_gelu);
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

    void (*activation_function)(neuron);
    void (*activation_function_derivative)(neuron);
};

neuron Neuron(double *x, double *w, double b, unsigned int input_size, void (*act)(neuron), void (*deriv)(neuron))
{
    neuron n = malloc(sizeof(struct neuron_));
    n->input_size = input_size;
    n->x = malloc(sizeof(value) * input_size);
    n->w = malloc(sizeof(value) * input_size);
    n->activation_function = act;
    n->activation_function_derivative = deriv;

    for (unsigned int i = 0; i < input_size; i++)
    {
        n->x[i] = setData(Value(NULL, NULL, forward_empty, backward_empty), x[i]);
        n->w[i] = setData(Value(NULL, NULL, forward_empty, backward_empty), w[i]);
    }

    n->b = setData(Value(NULL, NULL, forward_empty, backward_empty), b);

    return n;
}