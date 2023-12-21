#include "operation.h"
#include "value.h"
#include <stdio.h>
#include <stdlib.h>

int main_gradient(void)
{
    value v1 = Value(NULL, NULL, NULL);
    value v2 = Value(NULL, NULL, NULL);
    value v3 = Value(v1, v2, &mult);
    setGrad(v3, 1.0);

    setData(v1, 3.0);
    setData(v2, 2.0);

    forward(v3);
    backward(v3);

    printf("v1: %f\n", getData(v1));
    printf("v2: %f\n", getData(v2));
    printf("v3: %f\n", getData(v3));

    printf("v1: %f\n", getGrad(v1));
    printf("v2: %f\n", getGrad(v2));
    printf("v3: %f\n", getGrad(v3));

    draw(v3);

    freeValue(v3);
    freeValue(v2);
    freeValue(v1);

    return 0;
}
