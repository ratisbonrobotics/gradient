#ifndef PASS_FUNCTION_H
#define PASS_FUNCTION_H

#include "value.h"

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

#endif // PASS_FUNCTION_H