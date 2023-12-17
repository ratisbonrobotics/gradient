#include "boston_housing_dataset.h"
#include "mean_squared_error.h"
#include "network.h"
#include "neuron.h"
#include "operation.h"
#include <stdio.h>

int main_gradient(void)
{
    /* Build computational graph / Build model */
    network boston_housing_regression = Network(3, (unsigned int[]){12, 5, 1}, (operation[]){op_relu, op_relu, op_linear}, (operation[]){op_derivative_relu, op_derivative_relu, op_derivative_linear});

    neuron *inputs = getNeurons(getLayers(boston_housing_regression)[0]);
    value output = getY(getNeurons(getLayers(boston_housing_regression)[2])[0]);

    value target = Value(NULL, NULL, op_linear, op_derivative_linear);
    mean_squared_error mse = MSE(1, (value[]){output}, (value[]){target});

    /* Train model */
    double average_mse = 0.0;
    for (unsigned int i = 0; i < 10; i++)
    {
        for (unsigned int j = 0; j < 4; j++)
        {
            for (unsigned int k = 0; k < 100; k++)
            {
                for (unsigned int l = 0; l < 12; l++)
                {
                    setData(getY(inputs[l]), X_train[j * 100 + k][l]);
                }

                setData(target, Y_train[j * 100 + k]);

                forward_value(mse);
                backward_value(output);
            }
            update_value(output, 0.01);
            printf("Batch %d\n", j);
        }

        /* Test model */
        for (unsigned int j = 0; j < 100; j++)
        {
            for (unsigned int k = 0; k < 12; k++)
            {
                setData(getY(inputs[k]), X_test[j][k]);
            }
            setData(target, Y_test[j]);

            forward_value(mse);
            average_mse += getData(mse);
            printf("Sample %d: Error: %f\n", j, getData(mse));
        }

        printf("Training Epoch %d: Average MSE on test set: %f \n", i, average_mse / 100.0);
        average_mse = 0.0;
    }

    return 0;
}
