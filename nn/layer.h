#ifndef LAYER_H
#define LAYER_H

typedef struct layer_ *layer;

layer Layer(layer previous_layer, int size, int prev_size, operation act, operation act_deriv);

#endif // LAYER_H