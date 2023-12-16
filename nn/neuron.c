#include "neuron.h"
#include <stdlib.h>

struct neuron_
{
    double input;
};

neuron Neuron()
{
    neuron n = malloc(sizeof(struct neuron_));
    return n;
}