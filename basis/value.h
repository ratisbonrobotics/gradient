#ifndef VALUE_H
#define VALUE_H

#include "operation.h"

typedef struct value_ *value;

value Value(value child_left, value child_right, operation forward, operation backward);
void setData(value v, double data);
double getData(value v);
value getChildLeft(value v);
value getChildRight(value v);
operation getOperation(value v);
void setGrad(value v, double grad);
double getGrad(value v);
void forwardValue(value v);
void backwardValue(value v);
void updateValue(value v, double learning_rate);
void freeValue(value v);

#endif // VALUE_H