#ifndef VALUE_H
#define VALUE_H

typedef struct value_ *value;
value Value(value child_left, value child_right, void (*forward)(value), void (*backward)(value));
value setData(value v, double data);
double getData(value v);
value getChildLeft(value v);
value getChildRight(value v);
value setGrad(value v, double grad);
double getGrad(value v);

void forward_empty(value v);
void backward_empty(value v);
void forward_add(value v);
void backward_add(value v);
void forward_mult(value v);
void backward_mult(value v);
void forward_gelu(value v);
void backward_gelu(value v);
void forward_tanh(value v);
void backward_tanh(value v);
void forward_sigmoid(value v);
void backward_sigmoid(value v);

#endif // VALUE_H