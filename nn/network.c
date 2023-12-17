#include "network.h"
#include "layer.h"
#include <stdlib.h>

struct network_
{
    unsigned int size;
    layer *layers;
};

network Network(unsigned int network_size, unsigned int *layer_sizes, operation *layer_acts, operation *layer_act_derivs)
{
    network net = malloc(sizeof(struct network_));
    net->size = network_size;
    net->layers = calloc(network_size, sizeof(layer));

    net->layers[0] = Layer(NULL, layer_sizes[0], 0, layer_acts[0], layer_act_derivs[0]);
    for (unsigned int i = 1; i < network_size; i++)
    {
        net->layers[i] = Layer(net->layers[i - 1], layer_sizes[i], layer_sizes[i - 1], layer_acts[i], layer_act_derivs[i]);
    }

    return net;
}

neuron *getOutputs(network net)
{
    return getNeurons(net->layers[net->size - 1]);
}