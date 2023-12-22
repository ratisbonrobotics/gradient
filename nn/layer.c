#include "layer.h"
#include <assert.h>
#include <stdlib.h>

struct layer_
{
    unsigned int size;
    neuron *neurons;
};

layer Layer(value *inputs, unsigned int input_size, operation act, unsigned int size)
{
    layer l = malloc(sizeof(struct layer_));
    l->size = size;
    l->neurons = calloc(size, sizeof(neuron));

    for (unsigned int i = 0; i < size; i++)
    {
        l->neurons[i] = Neuron(inputs, input_size, act);
    }

    return l;
}

neuron *getNeurons(layer l)
{
    assert(l != NULL);
    return l->neurons;
}

unsigned int getSize(layer l)
{
    assert(l != NULL);
    return l->size;
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