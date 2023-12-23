#include "network.h"
#include "neuron.h"
#include "operation.h"
#include "value.h"
#include <stdio.h>
#include <stdlib.h>

#define BREADTH 5
#define DEPTH 2

int main_gradient(void)
{
    value v1 = Value(NULL, NULL, NULL);
    setData(v1, 3.0);
    value v2 = Value(NULL, NULL, NULL);
    setData(v2, 2.0);

    network net = Network((value[]){v1, v2}, 2, &leaky_relu, DEPTH, BREADTH);

    value inputs[BREADTH];
    for (int i = 0; i < BREADTH; i++)
    {
        inputs[i] = getY(getNeurons(getLayers(net)[DEPTH - 1])[i]);
    }

    neuron output = Neuron(inputs, BREADTH, &linear);
    value target = Value(NULL, NULL, NULL);
    setData(target, 10.0);
    value error = Value(getY(output), target, &sub);
    value squared_error = Value(error, NULL, &square);
    setGrad(squared_error, 1.0);

    for (int i = 0; i < 100; i++)
    {
        forward(squared_error);
        backward(squared_error);
        update(squared_error, 0.01);
        setData(target, 10.0);
        setData(v1, 3.0);
        setData(v2, 2.0);
        printf("error: %f\n", getData(squared_error));
        if (getData(squared_error) < 0.01)
            break;
    }

    char filename[100];
    snprintf(filename, sizeof(filename), "graphs/g_%d", 0);
    draw(squared_error, filename);

    freeAllValues();
    freeNetwork(net);
    freeNeuron(output);

    return 0;
}
