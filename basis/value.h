#ifndef VALUE_H
#define VALUE_H

#include "operation.h"
#include "tensor.h"

typedef struct value_ *value;

value Value(unsigned int x, unsigned int y, unsigned int z, value child_left, value child_right, operation op);
void setData(value v, tensor data);
tensor getData(value v);
value getChildLeft(value v);
value getChildRight(value v);
operation getOperation(value v);
void setGrad(value v, tensor grad);
tensor getGrad(value v);
void forward(value v);
void backward(value v);
void update(value v, double learning_rate);
void draw(value v, char *filename);
void freeAllValues(void);

#endif // VALUE_H