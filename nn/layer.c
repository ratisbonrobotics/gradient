#include <stdlib.h>
#include <assert.h>
#include "layer.h"

struct layer_
{
    unsigned int size;
    neuron *neurons;
};

layer Layer(layer previous_layer, int size, int prev_size, operation act, operation act_deriv)
{
    layer l = (layer)malloc(sizeof(struct layer_));
    l->size = size;
    l->neurons = calloc(size, sizeof(neuron));

    if (prev_size == 0)
    {
        /* input layer */
        for (unsigned int i = 0; i < size; i++)
        {
            l->neurons[i] = Neuron(NULL, 0, op_none, op_derivative_none);
        }
    }
    else
    {
        for (unsigned int i = 0; i < size; i++)
        {
            l->neurons[i] = Neuron(getNeurons(previous_layer), prev_size, act, act_deriv);
        }
    }

    return l;
}

unsigned int getSize(layer l)
{
    assert(l != NULL);
    return l->size;
}

neuron *getNeurons(layer l)
{
    assert(l != NULL);
    return l->neurons;
}
