#include "operation.h"
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/* operations */
static inline double op_add(double d1, double d2)
{
    return d1 + d2;
}

static inline double op_derivative_add(double d1, double d2)
{
    (void)d1;
    (void)d2;
    return 1.0;
}

static inline double op_sub(double d1, double d2)
{
    return d1 - d2;
}

static inline double op_derivative_sub(double d1, double d2)
{
    (void)d1;
    (void)d2;
    return 1.0;
}

static inline double op_mult(double d1, double d2)
{
    return d1 * d2;
}

static inline double op_derivative_mult(double d1, double d2)
{
    (void)d1;
    return d2;
}

/* activation functions */
static inline double op_linear(double x, double _unused)
{
    (void)_unused;
    return x;
}

static inline double op_derivative_linear(double x, double _unused)
{
    (void)x;
    (void)_unused;
    return 1.0;
}

static inline double op_square(double x, double _unused)
{
    (void)_unused;
    return pow(x, 2);
}

static inline double op_derivative_square(double x, double _unused)
{
    (void)_unused;
    return 2 * x;
}

static inline double op_abs(double x, double _unused)
{
    (void)_unused;
    return fabs(x);
}

static inline double op_abs_derivative(double x, double _unused)
{
    (void)x;
    (void)_unused;
    return 1.0;
}

static inline double op_relu(double x, double _unused)
{
    (void)_unused;
    return (x > 0.0) ? x : 0.0;
}

static inline double op_derivative_relu(double x, double _unused)
{
    (void)x;
    (void)_unused;
    return 1.0;
}

static inline double op_leaky_relu(double x, double _unused)
{
    (void)_unused;
    return (x > 0.0) ? x : 0.0001 * x;
}

static inline double op_derivative_leaky_relu(double x, double _unused)
{
    (void)_unused;
    return (x > 0.0) ? 1.0 : 0.0001;
}

static inline double op_sigmoid(double x, double _unused)
{
    (void)_unused;
    return 1 / (1 + exp(-x));
}

static inline double op_derivative_sigmoid(double x, double _unused)
{
    (void)_unused;
    return (1 - x) * x;
}

static inline double op_tanh(double x, double _unused)
{
    (void)_unused;
    return tanh(x);
}

static inline double op_derivative_tanh(double x, double _unused)
{
    (void)_unused;
    return (1 - pow(x, 2));
}

typedef char *operation_symbol;

struct operation_
{
    operation_function forward;
    operation_function backward;
    operation_symbol symbol;
};

struct operation_ add = {op_add, op_derivative_add, "+"};
struct operation_ sub = {op_sub, op_derivative_sub, "-"};
struct operation_ mult = {op_mult, op_derivative_mult, "*"};

struct operation_ linear = {op_linear, op_derivative_linear, "lin"};
struct operation_ square = {op_square, op_derivative_square, "^2"};
struct operation_ absolute = {op_abs, op_abs_derivative, "abs"};
struct operation_ relu = {op_relu, op_derivative_relu, "relu"};
struct operation_ leaky_relu = {op_leaky_relu, op_derivative_leaky_relu, "leaky_relu"};
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