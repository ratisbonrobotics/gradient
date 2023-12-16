#ifndef OPERATION_H
#define OPERATION_H

double op_add(double d1, double d2);
double op_derivative_add(double x, double grad);
double op_mult(double d1, double d2);
double op_derivative_mult(double x, double grad);
double op_sigmoid(double x, double _unused);
double op_derivative_sigmoid(double x, double grad);
double op_tanh(double x, double _unused);
double op_derivative_tanh(double x, double grad);
double op_gelu(double x, double _unused);
double op_derivative_gelu(double x, double grad);

#endif // OPERATION_H