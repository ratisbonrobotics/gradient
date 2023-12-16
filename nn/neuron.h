#ifndef NEURON_H
#define NEURON_H

#include "value.h"

typedef struct neuron_ *neuron;

neuron Neuron(double *x, double *w, double b, unsigned int input_size, operation act, operation act_deriv);

#endif // NEURON_H