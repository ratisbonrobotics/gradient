#ifndef NEURON_H
#define NEURON_H

#include "value.h"

typedef struct neuron_ *neuron;

neuron Neuron(neuron *children, double *w, double b, unsigned int input_size, operation act, operation act_deriv);
value getY(neuron n);

#endif // NEURON_H