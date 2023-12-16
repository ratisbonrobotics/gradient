#include "network.h"
#include "operation.h"
#include <stdio.h>

int main_gradient(void)
{

    network n = Network(3, (unsigned int[]){4, 3, 1}, (operation[]){op_sigmoid, op_sigmoid, op_sigmoid}, (operation[]){op_derivative_sigmoid, op_derivative_sigmoid, op_derivative_sigmoid});
    return 0;
}
