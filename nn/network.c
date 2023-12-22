#include "network.h"
#include "layer.h"
#include <stdlib.h>

struct network_
{
    unsigned int depth;
    unsigned int breadth;
    layer *layers;
};

network Network(value *inputs, unsigned int input_size, operation act, unsigned int depth, unsigned int breadth)
{
    network net = malloc(sizeof(struct network_));
    net->depth = depth;
    net->breadth = breadth;
    net->layers = calloc(depth, sizeof(layer));
    for (unsigned int i = 0; i < depth; i++)
    {
        if (i == 0)
        {
            net->layers[i] = Layer(inputs, input_size, act, breadth);
        }
        else
        {
            value inps[breadth];
            for (unsigned int j = 0; j < breadth; j++)
            {
                inps[j] = getY(getNeurons(net->layers[i - 1])[j]);
            }
            net->layers[i] = Layer(inps, breadth, act, breadth);
        }
    }
    return net;
}

layer *getLayers(network net)
{
    return net->layers;
}

unsigned int getDepth(network net)
{
    return net->depth;
}

unsigned int getBreadth(network net)
{
    return net->breadth;
}

void freeNetwork(network net)
{
    for (unsigned int i = 0; i < net->depth; i++)
    {
        freeLayer(net->layers[i]);
    }
    free(net->layers);
    free(net);
}