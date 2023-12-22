#ifndef NEURON_H
#define NEURON_H

#include "operation.h"
#include "value.h"

typedef struct neuron_ *neuron;

neuron Neuron(value *inputs, unsigned int input_size, operation act);
value getY(neuron n);
value *getW(neuron n);
value getB(neuron n);
unsigned int getInputSize(neuron n);
void freeNeuron(neuron n);

#endif // NEURON_H