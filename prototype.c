#include "layer.h"
#include "neuron.h"
#include "operation.h"
#include "value.h"
#include <stdio.h>
#include <stdlib.h>

#define LAYER_SIZE 15

int main_gradient(void)
{
    value v1 = Value(NULL, NULL, NULL);
    setData(v1, 3.0);
    value v2 = Value(NULL, NULL, NULL);
    setData(v2, 2.0);

    layer l = Layer((value[]){v1, v2}, 2, &leaky_relu, LAYER_SIZE);

    value inputs[LAYER_SIZE];
    for (int i = 0; i < LAYER_SIZE; i++)
    {
        inputs[i] = getY(getNeurons(l)[i]);
    }

    neuron output = Neuron(inputs, LAYER_SIZE, &linear);
    value target = Value(NULL, NULL, NULL);
    setData(target, 10.0);
    value error = Value(getY(output), target, &sub);
    value squared_error = Value(error, NULL, &square);
    setGrad(squared_error, 1.0);

    char filename[100];
    for (int i = 0; i < 100; i++)
    {
        forward(squared_error);
        snprintf(filename, sizeof(filename), "graphs/g_%d", i);
        draw(squared_error, filename);
        backward(squared_error);
        update(squared_error, 0.01);
        setData(target, 10.0);
        setData(v1, 3.0);
        setData(v2, 2.0);
        printf("error: %f\n", getData(squared_error));
        if (getData(squared_error) < 0.01)
            break;
    }

    freeValue(squared_error);
    freeValue(error);
    freeValue(target);
    freeValue(v2);
    freeValue(v1);

    return 0;
}
