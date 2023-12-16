#include <stdio.h>
#include "value.h"
#include "operation.h"

int main_gradient(void)
{
    value x1 = Value(NULL, NULL, NULL, NULL);
    value w1 = Value(NULL, NULL, NULL, NULL);
    value x1w1 = Value(x1, w1, op_mult, op_derivative_mult);

    value x2 = Value(NULL, NULL, NULL, NULL);
    value w2 = Value(NULL, NULL, NULL, NULL);
    value x2w2 = Value(x2, w2, op_mult, op_derivative_mult);

    value x1w1x2w2 = Value(x1w1, x2w2, op_add, op_derivative_add);
    value bias = Value(NULL, NULL, NULL, NULL);

    value x1w1x2w2bias = Value(x1w1x2w2, bias, op_add, op_derivative_add);

    value x1w1x2w2biasgelu = Value(x1w1x2w2bias, NULL, op_tanh, op_derivative_tanh);
    return 0;
}
