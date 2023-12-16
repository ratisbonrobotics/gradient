#ifndef NETWORK_H
#define NETWORK_H

#include "operation.h"

typedef struct network_ *network;

network Network(unsigned int network_size, unsigned int *layer_sizes, operation *layer_acts, operation *layer_act_derivs);

#endif // NETWORK_H