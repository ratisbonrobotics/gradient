#include "boston_housing_dataset.h"
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
    value inputs[12];
    for (int i = 0; i < 12; ++i)
    {
        inputs[i] = Value(NULL, NULL, NULL);
    }

    network net = Network(inputs, 12, &leaky_relu, DEPTH, BREADTH);

    value outputs[BREADTH];
    for (int i = 0; i < BREADTH; i++)
    {
        outputs[i] = getY(getNeurons(getLayers(net)[DEPTH - 1])[i]);
    }

    neuron output = Neuron(outputs, BREADTH, &linear);
    value target = Value(NULL, NULL, NULL);
    value error = Value(getY(output), target, &sub);
    value squared_error = Value(error, NULL, &square);
    setGrad(squared_error, 1.0);

    for (int l = 0; l < 200; l++)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 100; j++)
            {
                for (int k = 0; k < 12; k++)
                {
                    setData(inputs[k], X_train[j + i * 100][k]);
                }
                setData(target, Y_train[j + i * 100]);
                forward(squared_error);
                backward(squared_error);
            }
            if (l % 10 == 0)
                printf("epoch %d | batch: %d | error: %f\n", l, i, getData(squared_error));
            update(squared_error, 0.01);
        }
        for (int m = 0; m < 100; m++)
        {
            for (int n = 0; n < 12; n++)
            {
                setData(inputs[n], X_test[m][n]);
            }
            setData(target, Y_test[m]);
            forward(squared_error);
        }
        if (l % 10 == 0)
            printf("Test set | error: %f\n", getData(squared_error));
        setData(squared_error, 0.0);
    }

    char filename[100];
    snprintf(filename, sizeof(filename), "graphs/g_%d", 0);
    draw(squared_error, filename);

    freeAllValues();
    freeNetwork(net);
    freeNeuron(output);

    return 0;
}
