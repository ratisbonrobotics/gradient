#ifndef LAYER_H
#define LAYER_H

#include "operation.h"
#include "neuron.h"

typedef struct layer_ *layer;

layer Layer(layer previous_layer, int size, int prev_size, operation act, operation act_deriv);

unsigned int getSize(layer l);
neuron *getNeurons(layer l);

#endif // LAYER_H