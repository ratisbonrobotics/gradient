#ifndef NETWORK_H
#define NETWORK_H

#include "neuron.h"
#include "operation.h"

typedef struct network_ *network;

network Network(unsigned int network_size, unsigned int *layer_sizes, operation *layer_acts, operation *layer_act_derivs);

neuron *getOutputs(network net);

#endif // NETWORK_H