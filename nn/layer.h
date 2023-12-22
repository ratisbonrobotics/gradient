#ifndef LAYER_H
#define LAYER_H

#include "neuron.h"
#include "operation.h"
#include "value.h"

typedef struct layer_ *layer;

layer Layer(value *inputs, unsigned int input_size, operation act, unsigned int size);
neuron *getNeurons(layer l);
unsigned int getSize(layer l);

#endif // LAYER_H