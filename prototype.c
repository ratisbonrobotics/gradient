#include "network.h"
#include "operation.h"
#include <stdio.h>

int main_gradient(void)
{

    network boston_housing_regression = Network(3, (unsigned int[]){12, 5, 1}, (operation[]){op_relu, op_relu, op_linear}, (operation[]){op_derivative_relu, op_derivative_relu, op_derivative_linear});

    return 0;
}
