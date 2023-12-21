#include "operation.h"
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

static inline double op_linear(double x, double _unused)
{
    (void)_unused;
    return x;
}

static inline double op_derivative_linear(double _unused1, double _unused2)
{
    (void)_unused1;
    (void)_unused2;
    return 0;
}

static inline double op_add(double d1, double d2)
{
    return d1 + d2;
}

static inline double op_derivative_add(double _unused, double grad)
{
    (void)_unused;
    return grad;
}

static inline double op_sub(double d1, double d2)
{
    return d1 - d2;
}

static inline double op_derivative_sub(double _unused, double grad)
{
    (void)_unused;
    return grad;
}

static inline double op_mult(double d1, double d2)
{
    return d1 * d2;
}

static inline double op_derivative_mult(double x, double grad)
{
    return x * grad;
}

static inline double op_relu(double x, double _unused)
{
    (void)_unused;
    return (x > 0) ? x : 0;
}

static inline double op_derivative_relu(double x, double grad)
{
    return (x > 0) ? grad : 0;
}

static inline double op_sigmoid(double x, double _unused)
{
    (void)_unused;
    return 1 / (1 + exp(-x));
}

static inline double op_derivative_sigmoid(double x, double grad)
{
    return (1 - x) * x * grad;
}

static inline double op_tanh(double x, double _unused)
{
    (void)_unused;
    return tanh(x);
}

static inline double op_derivative_tanh(double x, double grad)
{
    return (1 - pow(x, 2)) * grad;
}

typedef char *operation_symbol;

struct operation_
{
    operation_function forward;
    operation_function backward;
    operation_symbol symbol;
};

struct operation_ linear = {op_linear, op_derivative_linear, "lin"};
struct operation_ add = {op_add, op_derivative_add, "+"};
struct operation_ sub = {op_sub, op_derivative_sub, "-"};
struct operation_ mult = {op_mult, op_derivative_mult, "*"};
struct operation_ relu = {op_relu, op_derivative_relu, "relu"};
struct operation_ sigmoid = {op_sigmoid, op_derivative_sigmoid, "sigmoid"};
struct operation_ tangent = {op_tanh, op_derivative_tanh, "tanh"};

operation_function getForward(operation op)
{
    return op->forward;
}

operation_function getBackward(operation op)
{
    return op->backward;
}

char *getSymbol(operation op)
{
    return op->symbol;
}