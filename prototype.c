#include <stdio.h>
#include "value.h"

int main_gradient(void)
{
    value x1 = Value(NULL, NULL, forward_empty, backward_empty);
    value w1 = Value(NULL, NULL, forward_empty, backward_empty);
    value x1w1 = Value(x1, w1, forward_mult, backward_mult);

    value x2 = Value(NULL, NULL, forward_empty, backward_empty);
    value w2 = Value(NULL, NULL, forward_empty, backward_empty);
    value x2w2 = Value(x2, w2, forward_mult, backward_mult);

    value x1w1x2w2 = Value(x1w1, x2w2, forward_add, backward_add);
    value bias = Value(NULL, NULL, forward_empty, backward_empty);

    value x1w1x2w2bias = Value(x1w1x2w2, bias, forward_add, backward_add);

    value x1w1x2w2biasgelu = Value(x1w1x2w2bias, NULL, forward_gelu, backward_gelu);
    return 0;
}
