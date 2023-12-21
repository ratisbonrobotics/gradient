#include "operation.h"
#include "value.h"
#include <stdio.h>
#include <stdlib.h>

int main_gradient(void)
{
    value v1 = Value(NULL, NULL, NULL);
    setData(v1, 3.0);
    value v2 = Value(NULL, NULL, NULL);
    setData(v2, 2.0);
    value output = Value(v1, v2, &mult);
    value target = Value(NULL, NULL, NULL);
    setData(target, 10.0);
    value error = Value(output, target, &sub);
    setGrad(error, 1.0);

    forward(error);
    draw(error, "first");
    backward(error);
    update(output, 0.01);

    forward(error);
    draw(error, "second");
    backward(error);
    update(output, 0.01);

    forward(error);
    draw(error, "third");
    backward(error);
    update(output, 0.01);

    freeValue(output);
    freeValue(v2);
    freeValue(v1);
    freeValue(target);
    freeValue(error);

    return 0;
}
