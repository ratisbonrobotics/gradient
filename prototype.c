#include "boston_housing_dataset.h"
#include "mean_squared_error.h"
#include "network.h"
#include "neuron.h"
#include "operation.h"
#include <stdio.h>

int main_gradient(void)
{
    network boston_housing_regression = Network(3, (unsigned int[]){12, 5, 1}, (operation[]){op_relu, op_relu, op_linear}, (operation[]){op_derivative_relu, op_derivative_relu, op_derivative_linear});

    value target = Value(NULL, NULL, op_linear, op_derivative_linear);
    value output = getY(getOutputs(boston_housing_regression)[0]);
    mean_squared_error mse = MSE(1, (value[]){output}, (value[]){target});

    for (unsigned int i = 0; i < 100; i++)
    {
        forward_value(mse);
        backward_value(output);
        update_value(output, 0.01);
    }

    return 0;
}
