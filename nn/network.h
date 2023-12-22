#ifndef NETWORK_H
#define NETWORK_H

#include "layer.h"
#include "operation.h"

typedef struct network_ *network;

network Network(value *inputs, unsigned int input_size, operation act, unsigned int depth, unsigned int breadth);
layer *getLayers(network net);
unsigned int getDepth(network net);
unsigned int getBreadth(network net);

#endif // NETWORK_H