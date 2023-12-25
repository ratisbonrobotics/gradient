#include "operation.h"
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/* operations */
static void op_add(tensor t, tensor a, tensor b)
{
    addTensor(t, a, b);
}

static void op_derivative_add(tensor t, tensor a, tensor b)
{
    fillTensor(t, 1.0);
}

static void op_sub(tensor t, tensor a, tensor b)
{
    subTensor(t, a, b);
}

static void op_derivative_sub(tensor t, tensor a, tensor b)
{
    fillTensor(t, 1.0);
}

static void op_hadamard(tensor t, tensor a, tensor b)
{
    hadamardTensor(t, a, b);
}

static void op_derivative_hadamard(tensor t, tensor a, tensor b)
{
    for (unsigned int i = 0; i < getX(t); i++)
    {
        for (unsigned int j = 0; j < getY(t); j++)
        {
            for (unsigned int k = 0; k < getZ(t); k++)
            {
                setDataTensor(t, i, j, k, getDataTensor(b, i, j, k));
            }
        }
    }
}

static void op_mult(tensor t, tensor a, tensor b)
{
    multTensor(t, a, b);
}

static void op_derivative_mult(tensor t, tensor a, tensor b)
{
    assert(getX(t) == getX(a) && getX(t) == getX(b));
    assert(getY(a) == getZ(b));
    assert(getY(t) == getY(b) && getZ(t) == getZ(a));

    for (unsigned int i = 0; i < getX(t); i++)
    { // Batch dimension
        for (unsigned int j = 0; j < getY(t); j++)
        { // Rows in 't', match rows in 'b'
            for (unsigned int k = 0; k < getZ(t); k++)
            {                                    // Columns in 't', match columns in 'a'
                fillDataTensor(t, i, j, k, 0.0); // Initialize to zero
                for (unsigned int l = 0; l < getY(a); l++)
                {                                                                                     // Sum over this dimension
                    setDataTensor(t, i, j, k, getDataTensor(t, i, j, k) + getDataTensor(b, i, l, j)); // Transposed access for 'b'
                }
            }
        }
    }
}

/* activation functions */
static void op_linear(tensor t, tensor a, tensor _unused_b)
{
    (void)_unused_b;
    copyTensor(t, a);
}

static void op_derivative_linear(tensor t, tensor _unused_a, tensor _unused_b)
{
    (void)_unused_a;
    (void)_unused_b;
    fillTensor(t, 1.0);
}

static double square(double x)
{
    return pow(x, 2);
}

static void op_hadamard_square(tensor t, tensor a, tensor _unused_b)
{
    (void)_unused_b;
    copyTensor(t, a);
    applyTensor(t, square);
}

static double double_(double x)
{
    return 2 * x;
}

static void op_derivative_hadamard_square(tensor t, tensor a, tensor _unused_b)
{
    (void)_unused_b;
    copyTensor(t, a);
    applyTensor(t, double_);
}

static void op_abs(tensor t, tensor a, tensor _unused_b)
{
    (void)_unused_b;
    copyTensor(t, a);
    applyTensor(t, fabs);
}

static void op_abs_derivative(tensor t, tensor _unused_a, tensor _unused_b)
{
    (void)_unused_a;
    (void)_unused_b;
    fillTensor(t, 1.0);
}

static void op_relu(tensor t, tensor a, tensor _unused_b)
{
    (void)_unused_b;
    for (unsigned int i = 0; i < getX(t); i++)
    {
        for (unsigned int j = 0; j < getY(t); j++)
        {
            for (unsigned int k = 0; k < getZ(t); k++)
            {
                double val = getDataTensor(a, i, j, k);
                setDataTensor(t, i, j, k, (val > 0.0) ? val : 0.0);
            }
        }
    }
}

static void op_derivative_relu(tensor t, tensor a, tensor _unused_b)
{
    (void)_unused_b;
    for (unsigned int i = 0; i < getX(t); i++)
    {
        for (unsigned int j = 0; j < getY(t); j++)
        {
            for (unsigned int k = 0; k < getZ(t); k++)
            {
                double val = getDataTensor(a, i, j, k);
                setDataTensor(t, i, j, k, (val > 0.0) ? 1.0 : 0.0);
            }
        }
    }
}

static void op_leaky_relu(tensor t, tensor a, tensor _unused_b)
{
    (void)_unused_b;
    const double alpha = 0.01; // Leaky ReLU coefficient
    for (unsigned int i = 0; i < getX(t); i++)
    {
        for (unsigned int j = 0; j < getY(t); j++)
        {
            for (unsigned int k = 0; k < getZ(t); k++)
            {
                double val = getDataTensor(a, i, j, k);
                setDataTensor(t, i, j, k, (val > 0.0) ? val : alpha * val);
            }
        }
    }
}

static void op_derivative_leaky_relu(tensor t, tensor a, tensor _unused_b)
{
    (void)_unused_b;
    const double alpha = 0.01; // Leaky ReLU coefficient
    for (unsigned int i = 0; i < getX(t); i++)
    {
        for (unsigned int j = 0; j < getY(t); j++)
        {
            for (unsigned int k = 0; k < getZ(t); k++)
            {
                double val = getDataTensor(a, i, j, k);
                setDataTensor(t, i, j, k, (val > 0.0) ? 1.0 : alpha);
            }
        }
    }
}

static void op_sigmoid(tensor t, tensor a, tensor _unused_b)
{
    (void)_unused_b;
    for (unsigned int i = 0; i < getX(t); i++)
    {
        for (unsigned int j = 0; j < getY(t); j++)
        {
            for (unsigned int k = 0; k < getZ(t); k++)
            {
                double val = getDataTensor(a, i, j, k);
                setDataTensor(t, i, j, k, 1.0 / (1.0 + exp(-val)));
            }
        }
    }
}

static void op_derivative_sigmoid(tensor t, tensor a, tensor _unused_b)
{
    (void)_unused_b;
    for (unsigned int i = 0; i < getX(t); i++)
    {
        for (unsigned int j = 0; j < getY(t); j++)
        {
            for (unsigned int k = 0; k < getZ(t); k++)
            {
                double sigmoid_val = getDataTensor(a, i, j, k);
                setDataTensor(t, i, j, k, sigmoid_val * (1.0 - sigmoid_val));
            }
        }
    }
}

static void op_tanh(tensor t, tensor a, tensor _unused_b)
{
    (void)_unused_b;
    for (unsigned int i = 0; i < getX(t); i++)
    {
        for (unsigned int j = 0; j < getY(t); j++)
        {
            for (unsigned int k = 0; k < getZ(t); k++)
            {
                double val = getDataTensor(a, i, j, k);
                setDataTensor(t, i, j, k, tanh(val));
            }
        }
    }
}

static void op_derivative_tanh(tensor t, tensor a, tensor _unused_b)
{
    (void)_unused_b;
    for (unsigned int i = 0; i < getX(t); i++)
    {
        for (unsigned int j = 0; j < getY(t); j++)
        {
            for (unsigned int k = 0; k < getZ(t); k++)
            {
                double tanh_val = getDataTensor(a, i, j, k);
                setDataTensor(t, i, j, k, 1.0 - pow(tanh_val, 2));
            }
        }
    }
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
struct operation_ hadamard = {op_hadamard, op_derivative_hadamard, ".*"};
struct operation_ mult = {op_mult, op_derivative_mult, "*"};

struct operation_ linear = {op_linear, op_derivative_linear, "lin"};
struct operation_ hadamard_square = {op_hadamard_square, op_derivative_hadamard_square, ".*^2"};
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