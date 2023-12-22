#include "neuron.h"
#include <assert.h>
#include <stdlib.h>
#include <time.h>

struct neuron_
{
    unsigned int input_size;
    value *w;
    value b;
    value y;
};

neuron Neuron(value *inputs, unsigned int input_size, operation act)
{
    srand((unsigned)time(NULL));

    neuron n = malloc(sizeof(struct neuron_));

    if (inputs == NULL)
    {
        n->input_size = 0;
        n->w = NULL;
        n->b = NULL;
        n->y = Value(NULL, NULL, NULL);
    }
    else
    {
        n->input_size = input_size;
        n->w = calloc(input_size, sizeof(value));

        value sigma_xiwi = NULL;

        for (unsigned int i = 0; i < input_size; i++)
        {
            n->w[i] = Value(NULL, NULL, NULL);
            setData(n->w[i], (double)rand() / (double)((unsigned)RAND_MAX / 2) - 1.0);

            value xiwi = Value(inputs[i], n->w[i], &mult);
            if (sigma_xiwi == NULL)
            {
                sigma_xiwi = Value(xiwi, NULL, &add);
            }
            else
            {
                sigma_xiwi = Value(xiwi, sigma_xiwi, &add);
            }
        }

        n->b = Value(NULL, NULL, NULL);
        setData(n->b, (double)rand() / (double)((unsigned)RAND_MAX / 2) - 1.0);
        value sigma_xiwi_bias = Value(sigma_xiwi, n->b, &add);

        n->y = Value(sigma_xiwi_bias, NULL, act);
    }

    return n;
}

value getY(neuron n)
{
    if (n == NULL)
    {
        return NULL;
    }
    else
    {
        return n->y;
    }
}

value *getW(neuron n)
{
    if (n == NULL)
    {
        return NULL;
    }
    else
    {
        return n->w;
    }
}

value getB(neuron n)
{
    if (n == NULL)
    {
        return NULL;
    }
    else
    {
        return n->b;
    }
}

unsigned int getInputSize(neuron n)
{
    if (n == NULL)
    {
        return 0;
    }
    else
    {
        return n->input_size;
    }
}
