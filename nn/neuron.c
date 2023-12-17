#include "neuron.h"
#include <assert.h>
#include <stdlib.h>

struct neuron_
{
    unsigned int input_size;
    value *w;
    value b;
    value y;
};

neuron Neuron(neuron *children, unsigned int input_size, operation act, operation act_deriv)
{
    neuron n = malloc(sizeof(struct neuron_));

    if (children == NULL)
    {
        /* input neuron */
        n->input_size = 0;
        n->w = NULL;
        n->b = NULL;
        n->y = Value(NULL, NULL, op_linear, op_derivative_linear);
    }
    else
    {
        n->input_size = input_size;
        n->w = calloc(input_size, sizeof(value));

        value sigma_xiwi = NULL;

        for (unsigned int i = 0; i < input_size; i++)
        {
            n->w[i] = Value(NULL, NULL, op_linear, op_derivative_linear);
            value xiwi = Value(getY(children[i]), n->w[i], op_mult, op_derivative_mult);
            if (sigma_xiwi == NULL)
            {
                sigma_xiwi = Value(xiwi, NULL, op_add, op_derivative_add);
            }
            else
            {
                sigma_xiwi = Value(xiwi, sigma_xiwi, op_add, op_derivative_add);
            }
        }

        n->b = Value(NULL, NULL, NULL, NULL);
        value sigma_xiwi_bias = Value(sigma_xiwi, n->b, op_add, op_derivative_add);

        n->y = Value(sigma_xiwi_bias, NULL, act, act_deriv);
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

void free_neuron(neuron n)
{
    assert(n != NULL);
    free_value(n->y);
    if (n->w != NULL)
    {
        free(n->w);
    }
    free(n);
}