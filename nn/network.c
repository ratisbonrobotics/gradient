#include "network.h"
#include "layer.h"

struct network_
{
    unsigned int size;
    layer *layers;
};

network Network(unsigned int size, unsigned int *layer_sizes, operation layer_acts, operation layer_act_derivs)
{
}