#include "layer.h"
#include <assert.h>
#include <stdlib.h>

struct layer_
{
    unsigned int size;
    neuron *neurons;
};

layer Layer(layer previous_layer, unsigned int size, unsigned int prev_size, operation act, operation act_deriv)
{
    layer l = (layer)malloc(sizeof(struct layer_));
    l->size = size;
    l->neurons = calloc(size, sizeof(neuron));

    if (prev_size == 0)
    {
        /* input layer */
        for (unsigned int i = 0; i < size; i++)
        {
            l->neurons[i] = Neuron(NULL, 0, op_linear, op_derivative_linear);
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

void freeLayer(layer l)
{
    assert(l != NULL);
    for (unsigned int i = 0; i < l->size; i++)
    {
        freeNeuron(l->neurons[i]);
    }
    free(l->neurons);
    free(l);
}