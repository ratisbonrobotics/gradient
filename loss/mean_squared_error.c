#include "mean_squared_error.h"
#include "operation.h"
#include <stdlib.h>

mean_squared_error MSE(unsigned int size, value *outputs, value *targets)
{
    value y_i_hat_minus_y_i_squared_sigma = NULL;

    for (unsigned int i = 0; i < size; i++)
    {
        value y_i_hat_minus_y_i_1 = Value(outputs[i], targets[i], op_sub, op_derivative_sub);
        value y_i_hat_minus_y_i_2 = Value(outputs[i], targets[i], op_sub, op_derivative_sub);
        value y_i_hat_minus_y_i_squared = Value(y_i_hat_minus_y_i_1, y_i_hat_minus_y_i_2, op_mult, op_derivative_mult);
        if (y_i_hat_minus_y_i_squared_sigma == NULL)
        {
            y_i_hat_minus_y_i_squared_sigma = y_i_hat_minus_y_i_squared;
        }
        else
        {
            y_i_hat_minus_y_i_squared_sigma = Value(y_i_hat_minus_y_i_squared_sigma, y_i_hat_minus_y_i_squared, op_add, op_derivative_add);
        }
    }

    value normalisation = Value(NULL, NULL, op_linear, op_derivative_linear);
    setData(normalisation, 1.0 / size);

    return Value(y_i_hat_minus_y_i_squared_sigma, normalisation, op_mult, op_derivative_mult);
}